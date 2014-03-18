#include <iostream>
#include <ctime>
#include <vector>
#include "../Configs.h"
#include "search/SearchUtil.h"

Configs* Configs::config = NULL;

int main(int argc, char** argv) {
  Configs* config = Configs::createInstance();
  config->read_params(argc, argv);

  double tstart, tstop, ttime;
  tstart = (double)clock();
  
  SearchUtil search;
  //search.load_index();
  
  tstop = (double)clock();
  ttime = (double)(tstop-tstart)/CLOCKS_PER_SEC;
  cout << endl << "***" << ttime << " second(s)." << "***" << endl;
}