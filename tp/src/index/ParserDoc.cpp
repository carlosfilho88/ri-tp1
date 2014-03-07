#include "ParserDoc.h"
using namespace std;

ParserDoc::ParserDoc(char *argv[]) {
  cr = new CollectionReader(argv[1], argv[2]);
  setHTML(string());
}

void ParserDoc::parse(Document& doc) {
  doc.clear();
  cr->getNextDocument(doc);
  setHTML(doc.getText());
  //cout << html << endl;
  htmlcxx::HTML::ParserSax::parse(getHTML());
}
void beginParsing() {}
void foundTag(Node node, bool isEnd) {}
void foundText(Node node) {
  cout << "foundText: " << node.text() << endl;
}
void foundComment(Node node) {}
void endParsing() {}

