#include <iostream>
#include <ctime>
#include <vector>
#include "index/ParserUtil.h"

int main(int argc, char** argv) {
  double tstart, tstop, ttime;
  tstart = (double)clock()/CLOCKS_PER_SEC;
  
  ParserUtil parser;
  parser.read_collection(argv);

  tstop = (double)clock()/CLOCKS_PER_SEC;
  ttime = tstop-tstart;
  cout << ttime << " second(s)." << endl;
}
