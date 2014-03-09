#include <iostream>
#include <ctime>
#include <vector>
#include "index/ParserUtil.h"

int main(int argc, char** argv) {
  double tstart, tstop, ttime;
  tstart = (double)clock();
  
  ParserUtil parser;
  parser.read_collection(argv);

  tstop = (double)clock();
  ttime = (double)(tstop-tstart)/CLOCKS_PER_SEC;
  cout << ttime << " second(s)." << endl;
}
