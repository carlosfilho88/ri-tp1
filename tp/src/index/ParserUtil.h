#ifndef __PARSER_UTIL_H__
#define __PARSER_UTIL_H__

#include <iostream>
#include <cstring>
#include <vector>
#include <cassert>
#include <unicode/utypes.h>
#include <unicode/unistr.h>
#include <unicode/translit.h>
#include <unicode/brkiter.h>
#include "gumbo.h"

using namespace std;

void extractWords(const string&);
string desaxUTF8(const string&);
string cleantext(GumboNode*);
const char* find_title(const GumboNode*);
vector<string> word(string&);

#endif /* __PARSER_UTIL_H__ */