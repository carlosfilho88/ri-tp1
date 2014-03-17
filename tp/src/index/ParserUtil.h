#ifndef __PARSER_UTIL_H__
#define __PARSER_UTIL_H__

#include <iostream>
#include <ctime>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <unordered_map>
#include <utility>
#include <CollectionReader.h>
#include <unicode/utypes.h>
#include <unicode/unistr.h>
#include <unicode/translit.h>
#include <unicode/brkiter.h>
#include <unicode/uniset.h>
#include "../Configs.h"
#include "gumbo.h"
#include "Triple.h"

using namespace std;
using namespace RICPNS;

class ParserUtil {

  string content;
  unsigned int num_words;
  
  public:
    ParserUtil();
    void read_collection();
    /*void extract_words(const string&);*/ //BreakIterator not working properly ):
    string normalize_text(const string&);
    string extract_text_html(GumboNode*);
    const char* find_title(const GumboNode*);
    vector<string> extract_terms(string&);
    void flush();
    void write_run();
    void read_vocabulary();
    void write_vocabulary();

};

#endif /* __PARSER_UTIL_H__ */