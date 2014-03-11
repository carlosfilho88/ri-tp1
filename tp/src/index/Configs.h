#ifndef __CONFIGS_H__
#define __CONFIGS_H__
#define RUN_SIZE 256
#include <iostream>
#include <string>

using namespace std;

class Configs {

  public:  
    static Config* Instance(void) {
      if(config == NULL) {
        config = new Config();
      }
      return config;
    }
 
    ~Config(){
      if(config != NULL){
        delete config;
        config = NULL;
      }
    }

    string FILENAME;
    string RUN_NAME;
    string INPUT_DIRECTORY;
    string INDEX_FILENAME;
    typedef unsigned int ui;
    ui KB = 1024;
    ui MB = KB * 1024;
    ui GB = MB * 1024;
    ui runSize;

    void read_params(int argc, char** argv) {

      for(unsigned int i = 0; i < argc; ++i){
        string param(argv[i]);

        if(param == "-r") {
          i++;
          if(sscanf(argv[i] , "%d", &runSize) != EOF)
            runSize = runSize*MB;
          else
            runSize = RUN_SIZE*MB;
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

};
#endif /* __CONFIGS_H__ */