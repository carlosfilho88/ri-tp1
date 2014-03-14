#include <iostream>
#include <ctime>
#include <vector>
#include "index/Configs.h"
#include "index/ParserUtil.h"
#include "index/RunUtil.h"

Configs* Configs::config = NULL;

int main(int argc, char** argv) {
  Configs* config = Configs::createInstance();
  config->read_params(argc, argv);

  double tstart, tstop, ttime;
  tstart = (double)clock();
  
  //ParserUtil parser;
  //parser.read_collection();

  RunUtil run;
  run.load();

  tstop = (double)clock();
  ttime = (double)(tstop-tstart)/CLOCKS_PER_SEC;
  cout << ttime << " second(s)." << endl;
}
