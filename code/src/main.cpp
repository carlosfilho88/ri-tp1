#include <iostream>
#include <stdio.h>
#include "../src/CollectionReader.h"
#include "../src/CollectionWriter.h"

int main(int argc, char *argv[]) {
  RICPNS::Document d;
  RICPNS::CollectionReader cr(argv[1], argv[2]);

  cr.getNextDocument(d);
  std::cout << ">>> " << "[" << d.getText() << "];" << std::endl;
}        