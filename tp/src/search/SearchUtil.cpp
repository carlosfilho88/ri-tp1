#include "SearchUtil.h"

  SearchUtil::SearchUtil() {}

  void SearchUtil::load_index() {
    Configs* config = Configs::createInstance();
    Inverted inv;
    stringstream filename;
    filename << config->INDEX_OUTPUT_DIRECTORY << config->INDEX_OUTPUT_FILENAME;
    ifstream index(filename.str(), ios::binary);
    int count = 0;
    if(index.is_open()) {
      while(index.good()) {
        ++count;
        index.read(reinterpret_cast<char *>(&inv), sizeof(inv));
        //cout << inv.id_term << "," << inv.doc_number << "," << inv.frequence <<"," << inv.occurrence << endl;
      }
      index.close();
      //cout << count << endl;
    }
  }

  void SearchUtil::load_vocabulary() {
    Configs* config = Configs::createInstance();
    Inverted inv;
    stringstream filename;
    filename << config->VOCABULARY_DIRECTORY << config->VOCABULARY_FILENAME;
    ifstream index(filename.str(), ios::binary);

    if(index.is_open()) {
      while(index.good()) {
        index.read(reinterpret_cast<char *>(&config->vocabulary), sizeof(config->vocabulary));
      }
      index.close();
    }
    cout << config->vocabulary.size() << endl;
    for(auto i = config->vocabulary.begin(); i != config->vocabulary.end(); ++i)
      cout << i->first << endl;
  }
