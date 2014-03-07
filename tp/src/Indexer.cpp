#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cctype>
#include <cerrno>
#include <CollectionReader.h>
#include <CharsetConverter.h>
#include "gumbo.h"
#include <iostream>
#include <string>
#include <time.h>
#include <vector>

using namespace std;
using namespace RICPNS;

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

#include <unicode/utypes.h>
#include <unicode/unistr.h>
#include <unicode/translit.h>
#include <unicode/brkiter.h>
#include "utf8.h"

#include <iostream>
#include <string>

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

string desaxUTF8(const string& str) {
  string result;
 
  UnicodeString source = UnicodeString::fromUTF8(StringPiece(str));
  UErrorCode status = U_ZERO_ERROR;
  Transliterator *accentsConverter = Transliterator::createInstance("Lower; NFD; Latin-ASCII; [\u0301] remove; NFC;", UTRANS_FORWARD, status);
  accentsConverter->transliterate(source);
  source.toUTF8String(result);

  return result;
}

void extractWords(const string& str) {
  string result;
  UnicodeString text = UnicodeString::fromUTF8(StringPiece("Cursos a distância de fotografia, estúdio fotográfico, serigrafia ou silk screen, representante comercial, bijuterias, operador de telemarketing, básico de informática, programador, lógica de programação, excel, digitação, almoxarife, comprador, eletricidade, telemensagens, recarga de cartuchos etc"));
  UnicodeString word;
  UErrorCode status = U_ZERO_ERROR;
  BreakIterator* wordIterator = BreakIterator::createSentenceInstance(Locale::getUS(), status);
  wordIterator->setText(text);

  int32_t start = wordIterator->first();

  for(int32_t end = wordIterator->next(); end != BreakIterator::DONE; start = end, end = wordIterator->next()) {
    text.extractBetween(start, end, word);
    cout << word.toUTF8String(result) << endl;
  }
}

vector<string> word(string& str) {
  vector<string> voc;
  char * dup = strdup(str.c_str());
  char * word;
  //cout << str << endl;
  word = strtok(dup," ,.!?():\"'@#$&*;|\\^~}{[]<>¹²³³£¢¬+_-=/\r\b\t\n");
  while (word != NULL) {
    voc.push_back(word);
    word = strtok(NULL, " ,.!?():\"'@#$&*;|\\^~}{[]<>¹²³³£¢¬+_-=/\r\b\t\n");
  }
  free(dup);
  return voc;
}

static string cleantext(GumboNode* node) {
  if (node->type == GUMBO_NODE_TEXT) {
    return string(node->v.text.text);
  } else if (node->type == GUMBO_NODE_ELEMENT && 
            node->v.element.tag != GUMBO_TAG_SCRIPT && 
            node->v.element.tag != GUMBO_TAG_STYLE && 
            node->v.element.tag != GUMBO_TAG_IMG && 
            node->v.element.tag != GUMBO_TAG_TITLE) {
    string contents = "";
    GumboVector* children = &node->v.element.children;
    for (int i = 0; i < children->length; ++i) {
      const string text = cleantext((GumboNode*) children->data[i]);
      if (i != 0 && !text.empty()) {
        contents.append(" ");
      }
      contents.append(reduce(text));
    }
    return contents;
  } else {
    return ""; 
  }
}

static const char* find_title(const GumboNode* root) {
  assert(root->type == GUMBO_NODE_ELEMENT);
  assert(root->v.element.children.length >= 2);

  const GumboVector* root_children = &root->v.element.children;
  GumboNode* head = NULL;
  for (unsigned int i = 0; i < root_children->length; ++i) {
    GumboNode* child = (GumboNode*)root_children->data[i];
    if (child->type == GUMBO_NODE_ELEMENT && child->v.element.tag == GUMBO_TAG_HEAD) {
      head = child;
      break;
    }
  }
  assert(head != NULL);

  GumboVector* head_children = &head->v.element.children;
  for (unsigned int i = 0; i < head_children->length; ++i) {
    GumboNode* child = (GumboNode*)head_children->data[i];
    if (child->type == GUMBO_NODE_ELEMENT && child->v.element.tag == GUMBO_TAG_TITLE) {
      if (child->v.element.children.length != 1) {
        return "<empty title>";
      }
      GumboNode* title_text = (GumboNode*)child->v.element.children.data[0];
      assert(title_text->type == GUMBO_NODE_TEXT);
      return title_text->v.text.text;
    }
  }
  return "<no title found>";
}

int main(int argc, char** argv) {
  CollectionReader cr(argv[1], argv[2]);
  Document doc;
  string contents;
  GumboOutput* output;
  doc.clear();
  char ch;
  unsigned long num_docs = 0;
  vector<string> voc;

  double tstart, tstop, ttime;
  tstart = (double)clock()/CLOCKS_PER_SEC;
  while (cr.getNextDocument(doc) && num_docs < 100) {
    contents = doc.getText();
    size_t begin = contents.find('<');
    contents = begin == contents.npos ? "" : contents.substr(begin, contents.size());
    output = gumbo_parse(contents.c_str());
    /*title = find_title(output->root);*/
    //printf("%s\n", title);
    //cout << contents << endl;
    contents = desaxUTF8(cleantext((GumboNode*)output->root));
    //app_utf8_is_ascii(contents.c_str(), contents.size());
    //cout << contents << endl;
    voc = word(contents);
    //for(vector<string>::const_iterator i = voc.begin(); i != voc.end(); ++i)
    //  cout << *i << ", ";

    doc.clear();
    num_docs++;
    cin >> ch;
  }
  tstop = (double)clock()/CLOCKS_PER_SEC;
  ttime = tstop-tstart; /*ttime is how long your code run */
  cout << num_docs << " document(s) in " << ttime << " second(s)." << endl;
  gumbo_destroy_output(&kGumboDefaultOptions, output);
}
