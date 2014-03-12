#include "Triple.h"
#include "RunUtil.h"
#include "index/Configs.h"

  RunUtil::RunUtil() {}

  void RunUtil::sort() {
    Configs* config = Configs::createInstance();
    ifstream file(config->FILENAME.c_str(), ios::binary);
    Inverted inv;

    if (file.is_open()) {
      file.read((char *)(&inv), sizeof(inv));
      cout << inv.id_term << "," << inv.doc_number << "," << inv.frequence << "," << inv.occurrence << endl;
    }

  }