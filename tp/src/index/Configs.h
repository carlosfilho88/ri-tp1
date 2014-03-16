#ifndef __CONFIGS_H__
#define __CONFIGS_H__
#define RUN_SIZE 256
#include <iostream>
#include <string>
#include <vector>
#include <sys/stat.h>
#include "Triple.h"

using namespace std;

class Configs {

  public:  
    static Configs* createInstance(void) {
      if(config == NULL) {
        config = new Configs();
      }
      return config;
    }
 
    ~Configs(){
      if(config != NULL){
        delete config;
        config = NULL;
      }
    }

    string FILENAME;
    string RUN_FILETYPE;
    string RUN_DIRECTORY;
    string INPUT_DIRECTORY;
    string INDEX_FILENAME;
    string INDEX_OUTPUT_FILENAME;
    string INDEX_OUTPUT_DIRECTORY;
    string VOCABULARY_DIRECTORY;
    string VOCABULARY_FILENAME;
    unsigned int RUN_NUM;
    unsigned int run_size;
    vector<unsigned int> runs;

    void read_params(int argc, char** argv) {
      mkdir("/tmp/runs", 0755);
      run_size = RUN_SIZE*1024*1024;
      RUN_NUM = 0;

      for(unsigned int i = 0; i < argc; ++i){
        string param(argv[i]);

        if(param == "-rs") {
          i++;
          run_size = atoi(argv[i])*1024*1024;
        } 
        else if(param == "-rf"){
          i++;
          RUN_FILETYPE = string(argv[i]);
        }
        else if(param == "-rd"){
          i++;
          RUN_DIRECTORY = string(argv[i]);
          mkdir(RUN_DIRECTORY.c_str(), 0755);
        }
        else if(param == "-id"){
          i++;
          INPUT_DIRECTORY = string(argv[i]);
        }
        else if(param == "-if"){
          i++;
          INDEX_FILENAME = string(argv[i]);
        }
        else if(param == "-od"){
          i++;
          INDEX_OUTPUT_DIRECTORY = string(argv[i]);
        }
        else if(param == "-of"){
          i++;
          INDEX_OUTPUT_FILENAME = string(argv[i]);
        }
        else if(param == "-vd"){
          i++;
          VOCABULARY_DIRECTORY = string(argv[i]);
        }
        else if(param == "-vf"){
          i++;
          VOCABULARY_FILENAME = string(argv[i]);
        }
      }
    }
    
    private:
      Configs() : FILENAME(""), 
                  RUN_FILETYPE(".run"), 
                  RUN_DIRECTORY("/tmp/runs/"), 
                  INPUT_DIRECTORY("/media/files"), 
                  INDEX_OUTPUT_DIRECTORY("/media/files/"), 
                  VOCABULARY_DIRECTORY("/media/files/"), 
                  INDEX_OUTPUT_FILENAME("inverted_index.bin"), 
                  VOCABULARY_FILENAME("vocabulary.bin"), 
                  INDEX_FILENAME("index.txt") {}

    static Configs* config;

};
#endif /* __CONFIGS_H__ */