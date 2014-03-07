#ifndef PARSERDOC_H_
#define PARSERDOC_H_

#include <iostream>
#include <CollectionReader.h>
#include <ParserSax.h>
#include <Node.h>

using namespace std;
using namespace htmlcxx; 
using namespace HTML; 
using namespace RICPNS;

class ParserDoc : protected ParserSax {
private:
  string html;

protected:
  virtual void beginParsing() {}
  virtual void foundTag(Node node, bool isEnd) {}
  virtual void foundText(Node node) {}
  virtual void foundComment(Node node) {}
  virtual void endParsing() {}

public:
  CollectionReader* cr;

  ParserDoc(char *argv[]);
  void parse(Document& doc);
  string getHTML() {
    return html;
  }

  void setHTML(string h) {
    html = h;
  } 
};
#endif /* PARSERDOC_H_ */