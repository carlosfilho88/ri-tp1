#ifndef __PARSER_UTIL_H__
#define __PARSER_UTIL_H__

#include <iostream>
#include <cstring>
#include <vector>
#include <cassert>
#include <algorithm>
#include <unicode/utypes.h>
#include <unicode/unistr.h>
#include <unicode/translit.h>
#include <unicode/brkiter.h>
#include <unicode/uniset.h>
#include "gumbo.h"
#include <CollectionReader.h>

using namespace std;
using namespace RICPNS;

class ParserUtil {

  string content;
  vector<string> terms;
  
  public:
    ParserUtil();
    void read_collection(char** argv);
    void extract_words(const string&);
    string normalize_text(const string&);
    string extract_text_html(GumboNode*);
    const char* find_title(const GumboNode*);
    vector<string> find_terms(string&);

};

#endif /* __PARSER_UTIL_H__ */