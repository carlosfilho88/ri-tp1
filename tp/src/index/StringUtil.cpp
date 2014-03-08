#include "StringUtil.h"

string normalize(string str) {
  unsigned char c;
  string normalized = string();
  for(unsigned int i = 0; i < str.length(); i++) {
    c = str.at(i);
    if (!
      ((c >= (char) 0x30 && c <= (char) 0x39) || //0-9
       (c >= (char) 0x41 && c <= (char) 0x5A) || //A-Z
       (c >= (char) 0x61 && c <= (char) 0x7A) || //a-z
       (c >= (char) 0xC0 && c <= (char) 0xD6) || //À-Ö
       (c >= (char) 0xD8 && c <= (char) 0xF6) || //Ø-ö
       (c >= (char) 0xF8 && c <= (char) 0xFF) //ø-ÿ
      )) {
      c = ' ';
    } else {
      if ((c >= (char) 0xC0 && c <= (char) 0xC6) || (c >= (char) 0xE0 && c <= (char) 0xE6)) c = 'a'; //À-Æ
      if ((c == (char) 0xC7) || (c == (char) 0xE7)) c = 'c'; //Ç
      if ((c >= (char) 0xC8 && c <= (char) 0xCB) || (c >= (char) 0xE8 && c <= (char) 0xEB)) c = 'e'; //È-Ë
      else if ((c >= (char) 0xCC && c <= (char) 0xCF) || (c >= (char) 0xEC && c <= (char) 0xEF)) c = 'i'; //Ì-Ï
      else if ((c == (char) 0xD0) || (c == (char) 0xF0)) c = 'd'; //Ð
      else if ((c == (char) 0xD1) || (c == (char) 0xF1)) c = 'n'; //Ñ
      else if ((c >= (char) 0xD2 && c <= (char) 0xD6) || (c >= (char) 0xF2 && c <= (char) 0xF6)) c = 'o'; //Ó-Ö
      else if ((c == (char) 0xD8) || (c == (char) 0xF8)) c = 'o'; //Ø
      else if ((c >= (char) 0xD9 && c <= (char) 0xDC) || (c >= (char) 0xF9 && c <= (char) 0xFC)) c = 'u'; //Ù-Ü
      else if ((c == (char) 0xDD) || (c == (char) 0xFD)) c = 'y'; //Ý
      else if ((c == (char) 0xDE) || (c == (char) 0xFE)) c = 'p'; //Þ
      else if ((c == (char) 0xDF) || (c == (char) 0xFF)) c = 'b'; //ß
    }
    normalized += c;
  }
  return normalized;
}

string trim(const string& str, const string& whitespace = " \t") {
  const auto strBegin = str.find_first_not_of(whitespace);
  if (strBegin == string::npos)
    return ""; // no content

  const auto strEnd = str.find_last_not_of(whitespace);
  const auto strRange = strEnd - strBegin + 1;

  return str.substr(strBegin, strRange);
}

string reduce(const string& str, const string& fill = " ", const string& whitespace = " \t") {
  // trim first
  auto result = trim(str, whitespace);

  // replace sub ranges
  auto beginSpace = result.find_first_of(whitespace);
  while (beginSpace != string::npos) {
    const auto endSpace = result.find_first_not_of(whitespace, beginSpace);
    const auto range = endSpace - beginSpace;

    result.replace(beginSpace, range, fill);

    const auto newStart = beginSpace + fill.length();
    beginSpace = result.find_first_of(whitespace, newStart);
  }

  return result;
}

char *latin9_to_utf8(const char *const string) {
  char *result;
  size_t n = 0;

  if (string) {
    const unsigned char *s = (const unsigned char *)string;

    while (*s)
      if (*s < 128) {
        s++;
        n += 1;
      } else
      if (*s == 164) {
        s++;
        n += 3;
      } else {
        s++;
        n += 2;
      }
  }

  /* Allocate n+1 (to n+7) bytes for the converted string. */
  result = (char*)malloc((n | 7) + 1);
  if (!result) {
    errno = ENOMEM;
    return NULL;
  }

  /* Clear the tail of the string, setting the trailing NUL. */
  memset(result + (n | 7) - 7, 0, 8);

  if (n) {
    const unsigned char  *s = (const unsigned char *)string;
    unsigned char        *d = (unsigned char *)result;

    while (*s)
      if (*s < 128) {
        *(d++) = *(s++);
      } else
      if (*s < 192) switch (*s) {
        case 164: *(d++) = 226; *(d++) = 130; *(d++) = 172; s++; break;
        case 166: *(d++) = 197; *(d++) = 160; s++; break;
        case 168: *(d++) = 197; *(d++) = 161; s++; break;
        case 180: *(d++) = 197; *(d++) = 189; s++; break;
        case 184: *(d++) = 197; *(d++) = 190; s++; break;
        case 188: *(d++) = 197; *(d++) = 146; s++; break;
        case 189: *(d++) = 197; *(d++) = 147; s++; break;
        case 190: *(d++) = 197; *(d++) = 184; s++; break;
        default:  *(d++) = 194; *(d++) = *(s++); break;
      } else {
        *(d++) = 195;
        *(d++) = *(s++) - 64;
      }
  }

  /* Done. Remember to free() the resulting string when no longer needed. */
  return result;
}

/*static bool isLegalUTF8(const unsigned char* source, int length) {
  unsigned char a;
  const unsigned char* srcptr = source + length;
  switch (length) {
    default: return false;
    // Everything else falls through when "true"...
    case 4: if ((a = (*--srcptr)) < 0x80 || a > 0xBF) return false;
    case 3: if ((a = (*--srcptr)) < 0x80 || a > 0xBF) return false;
    case 2: if ((a = (*--srcptr)) > 0xBF) return false;

    switch (*source) {
      // no fall-through in this inner switch
      case 0xE0: if (a < 0xA0) return false; break;
      case 0xED: if (a > 0x9F) return false; break;
      case 0xF0: if (a < 0x90) return false; break;
      case 0xF4: if (a > 0x8F) return false; break;
      default:   if (a < 0x80) return false;
    }
    case 1: if (*source >= 0x80 && *source < 0xC2) return false;
  }
  if (*source > 0xF4)
    return false;
  return true;
}
*/