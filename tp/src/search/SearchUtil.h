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

/*  struct {
    ifstream *file;
    //void (*operation)(ifstream&);
  } Filelist;*/

  public:
    SearchUtil();
    void load_index();
    void load_vocabulary();

};

#endif /* __SEARCH_UTIL_H__ */