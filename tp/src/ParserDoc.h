#ifndef PARSERDOC_H_
#define PARSERDOC_H_

#include <CollectionReader.h>
#include <ParserSax.h>
#include <Node.h>

using namespace std;
using namespace RICPNS;

class ParserDoc : protected htmlcxx::HTML::ParserSax {
public:
  void parse(char *argv[]);
};

#endif /* PARSERDOC_H_ */