#include <iostream>
#include <ctime>
#include <vector>
#include "index/Configs.h"
#include "index/ParserUtil.h"
#include "index/RunUtil.h"

int main(int argc, char** argv) {
  Configs conf;
  conf.read_params(argc, argv);

  double tstart, tstop, ttime;
  tstart = (double)clock();
  
  ParserUtil parser;
  parser.read_collection();

  RunUtil run;
  //run.sort();

  tstop = (double)clock();
  ttime = (double)(tstop-tstart)/CLOCKS_PER_SEC;
  cout << ttime << " second(s)." << endl;
}
