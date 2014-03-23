#include "SearchUtil.h"

  SearchUtil::SearchUtil() {}

  IndexSearch SearchUtil::find(const string& query) {
    Configs* config = Configs::createInstance();
    stringstream filename;
    filename << config->INDEX_OUTPUT_DIRECTORY << config->INDEX_OUTPUT_FILENAME;
    ifstream index(filename.str(), ios::binary);
    unsigned int count = 0;
    int id_term = 0;
    int doc_number = 0;
    unsigned int frequence = 0;
    unsigned int occurrence = 0;
    IndexSearch is;

    //cout << config->vocabulary_p.size() << endl;

    unsigned long position = config->vocabulary_p[query];
    //cout << "*** " << position << " ***" << endl;

    if(position > 0) {
      if(index.is_open()) {
        index.seekg(position-1);
        if(index.good()) {
          index.read(reinterpret_cast<char *>(&id_term), sizeof(id_term));
          is.id_term = (unsigned int)abs(id_term);
          //cout << id_term << endl;
          while(index.good()) {
            index.read(reinterpret_cast<char *>(&doc_number), sizeof(doc_number));
            is.occurrences.push_back(doc_number);
            if(doc_number > 0) {
              index.read(reinterpret_cast<char *>(&frequence), sizeof(frequence));
              is.frequence += frequence;
              //cout << doc_number << "," << frequence << "[";
              for (int i = 0; i < frequence; ++i) {
                index.read(reinterpret_cast<char *>(&occurrence), sizeof(occurrence));
                /*if (i == frequence-1)
                  cout << occurrence;
                else
                  cout << occurrence << ",";*/
              }
              //cout << "]" << endl;
            } else {
              break;
            }
          }
        }
        index.close();
      }
    }
    return is;
  }

  void SearchUtil::load_vocabulary() {
    Configs* config = Configs::createInstance();
    Inverted inv;
    stringstream filename;
    filename << config->VOCABULARY_DIRECTORY << config->VOCABULARY_FILENAME;
    ifstream voc(filename.str(), ios::in);
    cout << filename.str() << endl;

    if(voc.is_open()) {
      string word;
      unsigned long key;

      while (voc >> word >> key)
        config->vocabulary_p[word] = key;
      voc.close();
     /* for (auto i = config->vocabulary_p.begin(); i != config->vocabulary_p.end(); ++i)
        cout << i->first << ", " << i->second << endl;*/
    }
  }