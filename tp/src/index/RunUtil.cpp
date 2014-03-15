#include "RunUtil.h"

  vector<Inverted> inv_buffer;

  RunUtil::RunUtil() {}

  void RunUtil::load() {
    Configs* config = Configs::createInstance();
    const string ext = config->RUN_FILETYPE;
    vector<string> files;
    vector<ifstream *> open; 
    Inverted inv;
    inv_buffer.clear();

    if(get_runs(config->RUN_DIRECTORY, files) == 0) {

      //Opening and saving all RUN files in a vector
      for (auto i = 0; i < files.size(); ++i) {
        if(files[i] != "." && files[i] != "..") {
          ifstream* file = new ifstream(config->RUN_DIRECTORY + files[i], ios::binary);
          open.push_back(file);
          cout << "'" << i << "' openned." << endl;
        }
      }

      //For each RUN file, merge into a buffer (priority_queue) the same terms
      for (auto i = 0; i < open.size(); ++i) {
        if (open[i]->is_open()) {
          for(auto j = 0; open[i]->good(); ++j) {
            open[i]->read(reinterpret_cast<char *>(&inv), sizeof(inv));
            inv_buffer.push_back(inv);
            write_index();
          }
          cout << "'" << i << "' closed." << endl;
          open[i]->close();
        }
      }
    }
    if(inv_buffer.size() > 0)
      write_index();
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

  void RunUtil::write_index() {
  if(inv_buffer.size() > 0) {
    Configs* config = Configs::createInstance();
    FILE * file;
    Inverted inv;
    stringstream filename;
    filename << config->INDEX_OUTPUT_DIRECTORY << config->INDEX_OUTPUT_FILENAME;
    //cout << filename.str() << endl;
    file = fopen((filename.str()).c_str(), "wb+");

    if (file != NULL) {
      sort(inv_buffer.begin(), inv_buffer.end(), inv);
      for (auto i = 0; i < inv_buffer.size(); ++i){
        cout << inv_buffer[i].id_term << "," << inv_buffer[i].doc_number << "," << inv_buffer[i].frequence << "," << inv_buffer[i].occurrence << endl;
        fwrite((&inv_buffer[i]), 1, sizeof(inv_buffer[i]), file);
      }
      fclose(file);
      inv_buffer.clear();
    }
  }
/*  for (auto i = 0; i < inv_buffer.size(); ++i)
    cout << inv_buffer[i].id_term << "," << inv_buffer[i].doc_number << "," << inv_buffer[i].frequence << "," << inv_buffer[i].occurrence << endl;
  cout << "End inv_buffer" << endl;*/
} 