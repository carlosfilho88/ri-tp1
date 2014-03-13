#include "RunUtil.h"

  RunUtil::RunUtil() {}

  void RunUtil::load() {
    Configs* config = Configs::createInstance();
    const string ext = config->RUN_FILETYPE;
    vector<string> files;
    Inverted inv;

    if(get_runs(config->RUN_DIRECTORY, files) == 0) {
      for (auto i = 0; i < files.size(); ++i) {
        if(files[i] != "." && files[i] != "..") {
          ifstream file(config->RUN_DIRECTORY + files[i], ios::binary);

          if (file.is_open()) {
            while(file.good()) {
              file.read(reinterpret_cast<char *>(&inv), sizeof(inv));
              cout << inv.id_term << "," << inv.doc_number << "," << inv.frequence << "," << inv.occurrence << endl;
            }
            cout << "'" << files[i] << "' closed." << endl;
            file.close();
          }
        }
      }
    }
  } 

  int RunUtil::get_runs(string& dir, vector<string>& files) {
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
      cout << "Error(" << errno << ") opening runs directory: " << dir << endl;
      return errno;
    }
    while ((dirp = readdir(dp)) != NULL) {
      files.push_back(string(dirp->d_name));
    }
    closedir(dp);
    return 0;
  }