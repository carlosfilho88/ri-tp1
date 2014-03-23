#include <iostream>
#include <ctime>
#include <vector>
#include "Configs.h"
#include "search/SearchUtil.h"

Configs* Configs::config = NULL;

int main(int argc, char** argv) {
  Configs* config = Configs::createInstance();
  config->read_params(argc, argv);
  IndexSearch is1;
  IndexSearch is2;
  
  SearchUtil search;
  search.load_vocabulary();

  float tstart, tstop, ttime;
  tstart = (float)clock();
  is1 = search.find("sbt");
  is2 = search.find("globo");
  cout << is1.id_term << "," << is1.occurrences.size() << endl;
  cout << is2.id_term << "," << is2.occurrences.size() << endl;
  
  tstop = (float)clock();
  ttime = (float)(tstop-tstart)/CLOCKS_PER_SEC;
  cout << endl << "*** SEARCH time " << ttime << " second(s)." << "***" << endl;
}