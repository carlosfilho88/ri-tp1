#ifndef __TRIPLE_H__
#define __TRIPLE_H__
#include <algorithm>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

  struct Inverted {
    unsigned int id_term;
    unsigned int doc_number;
    unsigned int frequence;
    unsigned int occurrence;
    bool operator()(const Inverted &a, const Inverted &b) {
      if(a.id_term < b.id_term)
        return true;
      if(a.id_term > b.id_term)
        return false;
      if(a.doc_number < b.doc_number)
        return true;
      if(a.doc_number > b.doc_number)
        return false;
    };
  };

  struct IndexSearch {
    unsigned int id_term;
    unsigned int frequence;
    vector<unsigned int> occurrences;
  };

  typedef struct RUN {
    Inverted inv;
    unsigned int id_file;
    bool operator<(const RUN &r) const {
      if(inv.id_term < r.inv.id_term)
        return false;
      if(inv.id_term > r.inv.id_term)
        return true;
      if(inv.doc_number < r.inv.doc_number)
        return false;
      if(inv.doc_number > r.inv.doc_number)
        return true;
    };
    bool operator!=(const RUN &r) const {
      if(inv.id_term != r.inv.id_term
        && inv.doc_number != r.inv.doc_number
        && inv.frequence != r.inv.frequence
        && inv.occurrence != r.inv.occurrence)
        return false;
      else
        return true;
    };
    bool operator==(const RUN &r) const {
      if(inv.id_term == r.inv.id_term
        && inv.doc_number == r.inv.doc_number
        && inv.frequence == r.inv.frequence
        && inv.occurrence == r.inv.occurrence)
        return true;
      else
        return false;
    };
  } RUN;

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
