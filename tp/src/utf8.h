/*
 *  Reading and writing UTF-8 and ISO-Latin-1 streams.
 *
 *  Platform: Neutral
 *
 *  Version: 3.00  2001/05/05  First release.
 *  Version: 3.01  2001/09/18  Updated.
 *  Version: 3.08  2001/11/11  Added utf8_to_latin1, utf8_is_latin1.
 *  Version: 3.11  2001/12/12  Added unicode_char_to_utf8 and vice versa.
 *  Version: 3.12  2001/12/13  Added utf8_length function.
 *  Version: 3.29  2002/08/22  Fixed bugs in utf8_to_latin1, write_latin1.
 *  Version: 3.32  2002/09/04  Added correct_utf8 function.
 *  Version: 3.50  2004/01/11  Uses const keyword for some param strings.
 *  Version: 3.56  2005/08/09  Silenced some conversion warnings.
 *  Version: 3.62  2009/07/26  Bugfix in read_utf8_until.
 */

/* Copyright (c) L. Patrick and the Unicode organisation.

   This file is part of the App cross-platform programming package.
   You may redistribute it and/or modify it under the terms of the
   App Software License. See the file LICENSE.TXT for details.

   Portions of this code were developed by the Unicode organisation
   for free use by programmers, to promote the Unicode standard.
*/

/*
 *  UTF-8 is a way of reading and writing Unicode 32-bit characters
 *  to ordinary 8-bit communications streams.
 *
 *  The UTF-8 algorithm stores characters into variable-sized
 *  chunks. Characters in the range 0x00 to 0x7F fit into one
 *  byte, since these will be quite common (ASCII values).
 *  Characters with higher values fit into two, three, four,
 *  five, or six bytes, depending on the number of significant
 *  bits, according to the following pattern:
 *
 *  Bits  Pattern
 *  ----  -------
 *    7   0xxxxxxx
 *   11   110xxxxx 10xxxxxx
 *   16   1110xxxx 10xxxxxx 10xxxxxx
 *   21   11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
 *   26   111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
 *   32   111111xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx
 *
 *  As can be seen from the table, at most 32 bits can be stored
 *  using this algorithm (the x's mark where the actual bits go,
 *  the numbers signify the padding bits). The padding "10" at
 *  the start of a byte uniquely identifies a continuation byte,
 *  which is never used as the start of a UTF-8 character sequence,
 *  so if a stream is broken for some reason, the algorithm can
 *  skip those bytes to find the next start of a character.
 *
 *  ASCII is a 7-bit encoding for the English language alphabet
 *  and various digits and symbols. Its values range from 0x00 to 0x7F.
 *
 *  A superset of ASCII is ISO-Latin-1 (code page 8859-1). This is
 *  an 8-bit encoding for Western European languages, with values
 *  in the range 0x00 to 0xFF. The lower half of this range is
 *  the same as ASCII, while the upper half includes many accented
 *  characters.
 *
 *  Unicode is a superset of ISO-Latin-1, which mostly fits into
 *  16-bits, but which is actually a 32-bit encoding for most
 *  language symbols on Earth, including Eastern European, African,
 *  Asian, and many other languages. It allows a single document
 *  to contain mixtures of all languages.
 *
 *  This file contains functions for reading and writing Unicode
 *  and ISO-Latin-1 streams, to and from an array of 32-bit
 *  Unicode values in memory. Each 32-bit value is called a Char.
 */

#ifndef UTF8_H_
#define UTF8_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

typedef unsigned char      byte;
typedef unsigned long      Char;
#define IS_UTF8_EXTRA_BYTE(b) (((b)&0xC0)==0x80)

typedef enum UTF8ConversionResult {
	ConversionSuccess = 0, 	/* conversion successful */
	SourceExhausted = 1,	/* partial char in source, but hit end */
	SourceCorrupt = 2,	/* corrupted character in source */
	TargetExhausted = 4	/* no room in target for conversion */
} ConversionResult;		/* bit-field holding conversion result */

enum {
	Low6Bits = 0x3F,	/* 00111111 */
	High2Bits = 0xC0,	/* 11000000 */
	ByteMask = 0x00BF,	/* 10111111 */
	ContinueBits = 0x80	/* 10xxxxxx */
};

static const unsigned long ReplacementChar = 0x0000FFFDUL;
static const unsigned long MaximumChar     = 0x7FFFFFFFUL;

static const byte UTF8ExtraBytes[256] = {
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
	2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2, 3,3,3,3,3,3,3,3,4,4,4,4,5,5,5,5
};

static const byte FirstByteBits[7] = {
	0x00, 0x00, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC
};

static const unsigned long FirstByteMask[6] = {
	0xFF, 0x1F, 0x0F, 0x07, 0x03, 0x03
};


int unicode_to_utf8(const Char ** src_start, const Char * src_end,
			char ** dst_start, const char * dst_end)
{
	ConversionResult result = ConversionSuccess;
	register const Char * src = *src_start;
	register char * dst = *dst_start;

	while (src < src_end) {
		register unsigned long ch;
		register unsigned short bytes_to_write;
		register unsigned short extra_bytes;

		ch = *src++;

		if (ch < 0x80) {                bytes_to_write = 1;
		} else if (ch < 0x800) {        bytes_to_write = 2;
		} else if (ch < 0x10000) {      bytes_to_write = 3;
		} else if (ch < 0x200000) {     bytes_to_write = 4;
		} else if (ch < 0x4000000) {    bytes_to_write = 5;
		} else if (ch <= MaximumChar){  bytes_to_write = 6;
		} else {
			bytes_to_write = 2;
			ch = ReplacementChar;
		}

		dst += bytes_to_write;
		if (dst > dst_end) {
			dst -= bytes_to_write;
			result = TargetExhausted;
			break;
		}
		extra_bytes = bytes_to_write;
		while (--extra_bytes) {
			*--dst = (char) ((ch | ContinueBits) & ByteMask);
			ch >>= 6;
		}
		*--dst = (char) (ch | FirstByteBits[bytes_to_write]);

		dst += bytes_to_write;
	}
	*src_start = src;
	*dst_start = dst;
	return result;
}


int utf8_to_unicode(const char ** src_start, const char * src_end, Char ** dst_start, const Char * dst_end) {
	ConversionResult result = ConversionSuccess;
	register const char * src = *src_start;
	register Char * dst = *dst_start;

	while (src < src_end) {
		register Char ch;
		register unsigned short extra_bytes;

		extra_bytes = UTF8ExtraBytes[(unsigned char)*src];
		/*
		if (src + extra_bytes > src_end) {
			result |= SourceExhausted;
			break;
		}
		*/
		if (dst >= dst_end) {
			result |= TargetExhausted;
			break;
		}

		ch = (unsigned char)*src++;
		if (extra_bytes) {
			if (src >= src_end) {
				result |= SourceCorrupt;
				result |= SourceExhausted;
			}
			else if ((*src & High2Bits) == ContinueBits) {
				ch &= FirstByteMask[extra_bytes];
				do {
					ch <<= 6;
					ch |= ((*src++) & Low6Bits);
					if (--extra_bytes == 0)
						break;
					if (src >= src_end) {
						result |= SourceCorrupt;
						result |= SourceExhausted;
						break;
					}
					if ((*src & High2Bits) != ContinueBits) {
						result |= SourceCorrupt;
						break;
					}
				} while (1);
			} else {
				result |= SourceCorrupt;
			}
		}

		if (ch <= MaximumChar) {
			*dst++ = ch;
		} else {
			*dst++ = ReplacementChar;
		}
	}
	*src_start = src;
	*dst_start = dst;
	return result;
}

/*
 *  Convert a single Unicode character into a UTF-8 byte buffer.
 *  The buffer should be at least 7 bytes wide.
 */

/*
 *  Convert a UTF-8 char array to an ISO Latin 1 char array
 *  (non ISO Latin 1 characters will be distorted by this process).
 *  Assume the UTF-8 char array is correct.
 *  This function creates a new string containing the ISO Latin 1 data.
 *  It returns NULL if it runs out of memory.
 */
char *utf8_to_latin1(const char *utf8, int *bytes) {
	Char buf[1];
	Char *bp;
	const char *sp;
	long total = 0L;
	long nbytes = *bytes;
	char *dp;
	char *dest;

	dest = (char*)malloc(nbytes + 1);
	if (dest == NULL) {
		*bytes = 0;
		return NULL;
	}
	dp = dest;

	sp = utf8;
	while (nbytes > 0) {
		/* write one UTF-8 sequence into a Char buffer */
		bp = buf;
		utf8_to_unicode(&sp, sp+7, &bp, bp+1);
		/* determine what happened */
		nbytes -= (long) (sp - utf8);
		utf8 = sp;
		/* force Unicode Char into a Latin-1 char */
		*dp++ = (char) (buf[0] & 0x00FF);
		total++;
	}
	*dp = '\0';
	*bytes = total;
	return dest;
}

/*
 *  Convert a (possibly ISO Latin 1) char array to a UTF-8 char array,
 *  as best we can. If it is already correctly UTF 8 encoded, return
 *  the input string unchanged.
 *  This function may create a new string containing the UTF-8 data.
 *  It returns NULL if it runs out of memory.
 */
char *correct_utf8(const char *s, int *bytes) {
	Char buf[1];
	Char *bp;
	const Char *cbp;
	const char *sp;
	long total;
	long nbytes = *bytes;
	char *dp;
	char *dest;
	char tmp[8];
	char *tp;
	const char *original;
	int i;
	int diff = 0;

	total = nbytes;
	dest = (char*)malloc(total + 1);
	if (dest == NULL) {
		*bytes = 0;
		return NULL;
	}
	dp = dest;

	original = s;
	sp = s;
	while (nbytes > 0) {
		/* write one UTF-8 sequence into a Char buffer */
		bp = buf;
		utf8_to_unicode(&sp, sp+7, &bp, bp+1);

		/* determine what happened */
		nbytes -= (long) (sp - s);

		/* check for any difference, copy string also */
		cbp = buf;
		tp = tmp;
		unicode_to_utf8(&cbp, cbp+1, &tp, tp+7);
		i = (int) (dp-dest);
		if (total-i < tp-tmp) {
			total = i + (long) (tp-tmp);
			dest = (char*)realloc(dest, total+1);
			dp = dest + i;
		}
		for (i=0; i < (tp-tmp); i++) {
			if (s[i] != tmp[i])
				diff = 1;
			*dp++ = tmp[i];
		}

		/* move on to next char */
		s = sp;
	}
	*dp = '\0';
	*bytes = total;
	if (diff == 0) {
		free(dest);
		return (char *) original; /* cast away const */
	}
	return dest;
}

/*
 *  Return non-zero (true) if the given UTF-8 char array contains
 *  only ASCII characters, otherwise return zero. 
 */
int utf8_is_ascii(const char *utf8, long nbytes) {
	long i;

	for (i=0; i < nbytes; i++) {
		if (*utf8 & 0x80)
			return 0;
		utf8++;
	}
	return 1;
}

/*
 *  Return non-zero (true) if the given UTF-8 char array contains
 *  only ASCII and ISO Latin-1 characters, otherwise return zero. 
 */
int utf8_is_latin1(const char *utf8, long nbytes) {
	long i;

	for (i=0; i < nbytes; i++) {
		if (*utf8 & 0x80) {
			if ((*utf8 & 0xFC) != 0xC0) /* not 110-000xx */
				return 0;
			utf8++;
			i++;
			if (i >= nbytes)
				return 0;
			if ((*utf8 & 0xC0) != 0x80) /* not 10-xxxxxx */
				return 0;
		}
		utf8++;
	}
	return 1;
}

#endif