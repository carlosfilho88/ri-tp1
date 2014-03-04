#include <iostream>
#include <stdio.h>
#include "ParserDoc.h"

int main(int argc, char *argv[]) {
  ParserDoc pd;
  pd.parse(argv);
  return 0;
}
