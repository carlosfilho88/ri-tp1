#include "ParserDoc.h"

void parse(char *argv[]) {
  cout << argv[1] << " + " << argv[2] << endl;
  //CollectionReader cr(argv[1], argv[2]);
  //cr.getNextDocument(doc);
  //string html = doc.getText();
  //htmlcxx::HTML::ParserSax::parse(html);
}
/*
void ParserDoc::beginParsing() {}
void ParserDoc::foundTag(Node& node, bool isEnd) {}
void ParserDoc::foundText(Node& node) {
  cout << "foundText: " << text << endl;
}
void ParserDoc::foundComment(Node& node) {}
void ParserDoc::endParsing() {}*/