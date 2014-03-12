#ifndef __CONFIGS_H__
#define __CONFIGS_H__
#define RUN_SIZE 256
#include <iostream>
#include <string>
#include <vector>
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
    unsigned int RUN_NUM;
    unsigned int run_size;
    vector<unsigned int> runs;

    void read_params(int argc, char** argv) {
      run_size = RUN_SIZE*1024*1024;
      RUN_NUM = 0;

      for(unsigned int i = 0; i < argc; ++i){
        string param(argv[i]);

        if(param == "-r") {
          i++;
          run_size = atoi(argv[i])*1024*1024;
        } 
        if( param == "-d"){
          i++;
          INPUT_DIRECTORY = string(argv[i]);
        }
        else if(param == "-f"){
          i++;
          INDEX_FILENAME = string(argv[i]);
        }
      }
    }
    
    private:
      Configs() : FILENAME(""), 
                  RUN_FILETYPE(".run"), 
                  RUN_DIRECTORY("/tpm/runs"), 
                  INPUT_DIRECTORY("/media/files"), 
                  INDEX_FILENAME("index.txt") {}

    static Configs* config;

};
#endif /* __CONFIGS_H__ */