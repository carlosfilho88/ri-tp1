#include <iostream>
#include <stdio.h>
#include <CollectionReader.h>
#include <CollectionWriter.h>
#include <ParserDom.h>

using namespace std;
using namespace htmlcxx;

int main(int argc, char *argv[]) {
  RICPNS::Document d;
  RICPNS::CollectionReader cr(argv[1], argv[2]);

  cr.getNextDocument(d);

  string html = d.getText();
    HTML::ParserDom parser;
  tree<HTML::Node> dom = parser.parseTree(html);
  
  tree<HTML::Node>::iterator it = dom.begin();
  tree<HTML::Node>::iterator end = dom.end();
  for (; it != end; ++it) {
    cout << "Tag=" << it->tagName() << " content=\"" << it->content(html) << "\"\n";
      if (it->tagName() == "link") {
        it->parseAttributes();

        pair<bool, string> p = it->attribute("href");
        if(p.first) {
          cout << "Found a link: ";
          cout << p.second.c_str() << endl;
        }
      } else if (it->tagName() == "body") {
        cout << "Found body, text=\"" << it->text() << "\"" << " closing=\"" << it->closingText() << "\"\n";
    } else {
      cout << "Tag=" << it->tagName() << " content=\"" << it->content(html) << "\"\n";
    }
  }

  it = dom.begin();
  end = dom.end();
  for (; it != end; ++it) {
    if ((!it->isTag()) && (!it->isComment())) {
      cout << "Found text: ";
      cout << it->text() << endl;
    }
  }
  return 0;
}