#ifndef __RUN_UTIL_H__
#define __RUN_UTIL_H__

#include <ios>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include "Configs.h"
#include "Triple.h"
#include <dirent.h>
#include <errno.h>

class RunUtil {

/*  struct {
    ifstream *file;
    //void (*operation)(ifstream&);
  } Filelist;*/

  public:
    RunUtil();
    void load();
    int get_runs(string& path, vector<string>& files);
    void write_index();

};

#endif /* __RUN_UTIL_H__ */