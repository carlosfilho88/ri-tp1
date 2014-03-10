#ifndef __PARSER_UTIL_H__
#define __PARSER_UTIL_H__

#include <iostream>
#include <fstream>
#include <cstring>
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
#include "gumbo.h"
#include "Triple.h"

using namespace std;
using namespace RICPNS;

class ParserUtil {

  string content;
  unordered_map<string, unsigned int> vocabulary;
  unsigned int num_words;
  
  public:
    ParserUtil();
    void read_collection(char** argv);
    /*void extract_words(const string&);*/ //BreakIterator not working properly ):
    string normalize_text(const string&);
    string extract_text_html(GumboNode*);
    const char* find_title(const GumboNode*);
    vector<string> extract_terms(string&);
    void write_to_index(vector<Triple>& triples, unordered_map<unsigned int, vector<unsigned int>>& frequences);

};

#endif /* __PARSER_UTIL_H__ */