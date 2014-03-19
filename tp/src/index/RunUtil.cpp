#include "RunUtil.h"

  priority_queue<RUN, vector<RUN>> pq;
  unordered_map<unsigned int, unsigned long> offset;
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
    int current_term = -1;
    int current_doc = -1;
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

      unsigned int term_frequence = 0;
      int markdown = 0;
      //Merging RUNs
      while(!pq.empty()) {
        r = pq.top();
        if(current_term != r.inv.id_term) {
          current_term = r.inv.id_term;
          current_doc = r.inv.doc_number;
          current_position = ftell(index_file);
          offset[current_term] = current_position+1;
          markdown = -(int)(r.inv.id_term);
          //cout << markdown << endl;
          fwrite((&markdown), 1, sizeof(markdown), index_file);
          fwrite((&r.inv.doc_number), 1, sizeof(r.inv.doc_number), index_file);
          fwrite((&r.inv.frequence), 1, sizeof(r.inv.frequence), index_file);
          fwrite((&r.inv.occurrence), 1, sizeof(r.inv.occurrence), index_file);
        } else if (current_term == r.inv.id_term && current_doc != r.inv.doc_number) {
          ++term_frequence;
          current_doc = r.inv.doc_number;
          fwrite((&r.inv.doc_number), 1, sizeof(r.inv.doc_number), index_file);
          fwrite((&r.inv.frequence), 1, sizeof(r.inv.frequence), index_file);
          fwrite((&r.inv.occurrence), 1, sizeof(r.inv.occurrence), index_file);
        } else if(r.inv.id_term == current_term && r.inv.doc_number == current_doc) {
          ++term_frequence;
          fwrite((&r.inv.occurrence), 1, sizeof(r.inv.occurrence), index_file);
        }
        
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
      
      for (auto i = config->vocabulary.begin(); i != config->vocabulary.end(); ++i)
        config->vocabulary_p[i->first] = offset[i->second];

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