#ifndef __TRIPLE_H__
#define __TRIPLE_H__
#include <algorithm> 

struct Inverted {
  unsigned int id_term;
  unsigned int doc_number;
  unsigned int frequence;
  unsigned int occurrence;
  bool operator () (const Inverted &a, const Inverted &b) {
    if(a.id_term < b.id_term)
      return true;
    if(a.id_term > b.id_term)
      return false;
    if(a.doc_number < b.doc_number)
      return true;
    if(a.doc_number > b.doc_number)
      return false;
  }
};

class Triple {

  public:
    unsigned int id_term;
    unsigned int doc_number;
    unsigned int occurrence;

    Triple() {}

    Triple(unsigned int id, unsigned int doc) {
      id_term = id; 
      doc_number = doc;
    }

    Triple(unsigned int id, unsigned int doc, unsigned int occ) {
      id_term = id;
      doc_number = doc;
      occurrence = occ;
    }
};

#endif /* __TRIPLE_H__ */
