#ifndef __SEARCH_UTIL_H__
#define __SEARCH_UTIL_H__

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <iterator>
#include "../Configs.h"
#include "index/Triple.h"

class SearchUtil {

  public:
    SearchUtil();
    void load_index();
    void load_vocabulary();
    void find(const string& word);

};

#endif /* __SEARCH_UTIL_H__ */