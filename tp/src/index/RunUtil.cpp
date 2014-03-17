#include "RunUtil.h"

  priority_queue<RUN, vector<RUN>> pq;
  unordered_map<int, unsigned long> offset;
  RUN r;

  RunUtil::RunUtil() {}

  void RunUtil::merge() {
    Configs* config = Configs::createInstance();
    FILE * index_file;
    stringstream filename;
    filename << config->INDEX_OUTPUT_DIRECTORY << config->INDEX_OUTPUT_FILENAME;
    index_file = fopen((filename.str()).c_str(), "wb+");
    const string ext = config->RUN_FILETYPE;
    vector<string> files;
    vector<ifstream *> open; 
    Inverted inv;
    int position = -1;
    unsigned long current_position = 0;

    if(get_runs(config->RUN_DIRECTORY, files) == 0) {

      //Opening and saving all RUN files in a vector
      for (auto i = 0; i < files.size(); ++i) {
        if(files[i] != "." && files[i] != "..") {
          ifstream* file = new ifstream(config->RUN_DIRECTORY + files[i], ios::binary);
          open.push_back(file);
          //cout << "'" << i << "' openned." << endl;
        }
      }

      //Initialize priority_queue with first element for each RUN
      for (auto i = 0; i < open.size(); ++i) {
        if (open[i]->is_open() && open[i]->good()) {
          open[i]->read(reinterpret_cast<char *>(&inv), sizeof(inv));
          r.inv = inv;
          r.id_file = i;
          pq.push(r);
        }
      }

      //Merging RUNs
      while(!pq.empty()) {
        r = pq.top();
        if(position != r.inv.id_term) {
          position = r.inv.id_term;
          current_position = ftell(index_file);
          offset[position] = current_position;
        }

        if (index_file != NULL)
          fwrite((&r.inv), 1, sizeof(r.inv), index_file);
        
        pq.pop();
        if (open[r.id_file]->is_open() && open[r.id_file]->good()) {
          open[r.id_file]->read(reinterpret_cast<char *>(&r.inv), sizeof(r.inv));
          pq.push(r);
        } /*else {
          cout << "->" << r.inv.id_term << "," << r.inv.doc_number << "," << r.inv.frequence << "," << r.inv.occurrence << endl;
        }*/
      }

      for (auto i = 0; i < open.size(); ++i) 
        open[i]->close();
      
      for (auto i = config->vocabulary.begin(); i != config->vocabulary.end(); ++i) {
        i->second = offset[i->second];
        cout << i->first << ";" << i->second << endl;
      }

    }
    fclose(index_file);
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