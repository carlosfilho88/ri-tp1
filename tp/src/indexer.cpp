#include <iostream>
#include <stdio.h>
#include <CollectionReader.h>
#include <CollectionWriter.h>

int main(int argc, char *argv[]) {
  RICPNS::Document d;
  RICPNS::CollectionReader cr(argv[1], argv[2]);

  cr.getNextDocument(d);
  std::cout << ">>> " << "[" << d.getText() << "];" << std::endl;
}        