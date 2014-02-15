#include <iostream>
#include <stdio.h>
#include <CollectionReader.h>
#include <CollectionWriter.h>
#include <htmlcxx/html/ParserDom.h>

using namespace std;
using namespace htmlcxx;

int main(int argc, char *argv[]) {
  RICPNS::Document d;
  RICPNS::CollectionReader cr(argv[1], argv[2]);

  cr.getNextDocument(d);

  string html = d.getText();
  HTML::ParserDom parser;
  tree<HTML::Node> dom = parser.parseTree(html);
  cout << dom << endl;
}