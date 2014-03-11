#ifndef __TRIPLE_H__
#define __TRIPLE_H__

using namespace std;

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

typedef struct {
  unsigned int id_term;
  unsigned int doc_number;
  unsigned int frequence;
  unsigned int occurrence;
} Inverted;

#endif /* __TRIPLE_H__ */
