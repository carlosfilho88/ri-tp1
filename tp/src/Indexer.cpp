#include <iostream>
#include <ctime>
#include <vector>
#include "Configs.h"
#include "index/ParserUtil.h"
#include "index/RunUtil.h"
#include "search/SearchUtil.h"

Configs* Configs::config = NULL;

int main(int argc, char** argv) {
  Configs* config = Configs::createInstance();
  config->read_params(argc, argv);

  float tstart, tstop, ttime;
  tstart = (float)clock();
  
  ParserUtil parser;
  parser.read_collection();

  RunUtil run;
  run.merge();

  tstop = (float)clock();
  ttime = (float)(tstop-tstart)/CLOCKS_PER_SEC;
  cout << endl << "*** Total time: " << ttime << " second(s)" << "***" << endl;
}
