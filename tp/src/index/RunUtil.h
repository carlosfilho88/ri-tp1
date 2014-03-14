#ifndef __RUN_UTIL_H__
#define __RUN_UTIL_H__

#include <ios>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "Configs.h"
#include "Triple.h"
#include <dirent.h>
#include <errno.h>

class RunUtil {

  struct {
    const char *filename;
    void (*operation)(ifstream&);
  } filelist;

  public:
    RunUtil();
    void load();
    int get_runs(string& path, vector<string>& files);
};

#endif /* __RUN_UTIL_H__ */