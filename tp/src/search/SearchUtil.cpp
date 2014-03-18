#include "SearchUtil.h"

  SearchUtil::SearchUtil() {}

  void SearchUtil::load_index() {
    Configs* config = Configs::createInstance();
    Inverted inv;
    stringstream filename;
    filename << config->INDEX_OUTPUT_DIRECTORY << config->INDEX_OUTPUT_FILENAME;
    ifstream index(filename.str(), ios::binary);
    int count = 0;

    unsigned int doc_number = 0;
    unsigned int frequence = 0;
    unsigned int occurrence = 0;
    vector<unsigned int> occurrences;
    if(index.is_open()) {
      while(index.good()) {
        ++count;
        index.read(reinterpret_cast<char *>(&doc_number), sizeof(doc_number));
        index.read(reinterpret_cast<char *>(&frequence), sizeof(frequence));
        cout << doc_number << "," << frequence << "[";
        for (int i = 0; i < frequence; ++i) {
          index.read(reinterpret_cast<char *>(&occurrence), sizeof(occurrence));
          if (i == frequence-1)
            cout << occurrence;
          else
            cout << occurrence << ",";
        }
      cout << "]" << endl;

      }
      index.close();
    }
  }

  void SearchUtil::load_vocabulary() {
    Configs* config = Configs::createInstance();
    Inverted inv;
    stringstream filename;
    filename << config->VOCABULARY_DIRECTORY << config->VOCABULARY_FILENAME;
    ifstream voc(filename.str(), ios::in);

    if(voc.is_open()) {
      string word;
      unsigned int key;

      while (voc >> word >> key)
        config->vocabulary[word] = key;
      voc.close();
    }
  }

  void SearchUtil::find(const string& word) {
    Configs* config = Configs::createInstance();
  }
