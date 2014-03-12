#ifndef __CONFIGS_H__
#define __CONFIGS_H__
#define RUN_SIZE 256
#include <iostream>
#include <string>

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
    string INPUT_DIRECTORY;
    string INDEX_FILENAME;
    unsigned int run_size;

    void read_params(int argc, char** argv) {

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
      Configs() : FILENAME(""), RUN_FILETYPE(".run"), INPUT_DIRECTORY("../../files"), INDEX_FILENAME("indexToCompressedColection.txt") {}

    static Configs* config;

};
#endif /* __CONFIGS_H__ */