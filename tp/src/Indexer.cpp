#include <iostream>
#include <ctime>
#include <vector>
#include <CollectionReader.h>
#include "gumbo.h"
#include "index/StringUtil.h"
#include "index/ParserUtil.h"

using namespace std;
using namespace RICPNS;

int main(int argc, char** argv) {
  CollectionReader cr(argv[1], argv[2]);
  Document doc;
  string contents;
  GumboOutput* output;
  size_t begin;
  doc.clear();
  char ch;
  unsigned long num_docs = 0;
  vector<string> voc;

  double tstart, tstop, ttime;
  tstart = (double)clock()/CLOCKS_PER_SEC;
  while (cr.getNextDocument(doc) && num_docs < 100) {
    contents = doc.getText();
    begin = contents.find('<');
    contents = begin == contents.npos ? "" : contents.substr(begin, contents.size());
    output = gumbo_parse(contents.c_str());
    /*title = find_title(output->root);
    printf("%s\n", title);*/
    contents = desaxUTF8(cleantext((GumboNode*)output->root));
    gumbo_destroy_output(&kGumboDefaultOptions, output);
    voc = word(contents);
    cout << contents << endl;
    //for(vector<string>::const_iterator i = voc.begin(); i != voc.end(); ++i)
    //  cout << *i << ", ";

    doc.clear();
    num_docs++;
    cin >> ch;
  }
  tstop = (double)clock()/CLOCKS_PER_SEC;
  ttime = tstop-tstart;
  cout << num_docs << " document(s) in " << ttime << " second(s)." << endl;
}
