// BinEweControl.cpp
#include "ControlEwe.h"
#include <sys/wait.h>
#include <unistd.h>
//#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
int main(int argc, char** argv){
  string memoryFlag = (argc > 1) ?  string(argv[1]) : "" ;
  char* memoryName;
  string cfgFile = (argc > 3) ?  string(argv[3]) : "" ;
  string mewFile = "", bewFile = "";
  bool standartInput = false;
  vector<string> bewsFiles;
  int bewsSize;
  if(memoryFlag == "-n"){
    if(argc <= 2){
      cout << "Usage: " << argv[0] << " -n <nommemcom> [<ficherocfg>]" << endl;
      return 1;
    }else{
      if(cfgFile == ""){
	standartInput = true;
      }
    }
  }else{
    cout << "Usage: " << argv[0] << " -n <nommemcom> [<ficherocfg>]" << endl;
    return 1;
  }
  if(!standartInput){
    ifstream readCfgFile(cfgFile.c_str());
    readCfgFile >> mewFile;
    while(readCfgFile >> bewFile){
      bewsFiles.push_back(bewFile);
    }
    readCfgFile.close(); // avoiding that a buffer stays open (previous experiences)
  }else{
    cout << "Ingrese el fichero .mew" << endl;
    cin >> mewFile;
    cout << "Ingrese la cantidad de .bew que va a ingresar" << endl;
    cin >> bewsSize;
    for(int i = 0; i < bewsSize; ++i){
      cin >> bewFile;
      bewsFiles.push_back(bewFile);
    }
  }
  int BinEwe =  bewsFiles.size();
  cout << "xx " << BinEwe << endl; 
  int link[2], status;
  memoryName = argv[2];
  char in[4096];
  vector<string> bews;
  if(pipe(link) == -1){
    exit(EXIT_FAILURE);
  }
  ControlEwe Control(memoryName, mewFile);
  Control.readMew(); //Read Mew.mew and Create Memory
  pid_t processes[BinEwe]; // Run With Exec -> As a Bash Command
  for(int files =0; files< BinEwe; ++files){
    cout << memoryName << " == " << bewsFiles[files] << endl;
    if ((processes[files] = ::fork()) == -1) {
      perror("Exec Process Failed");
      exit(EXIT_FAILURE);
    }else if(processes[files] == 0){
      dup2(link[1], STDOUT_FILENO);
      close(link[0]);
      close(link[1]);
      execlp( "./BinEweInterpreter", "./BinEweInterpreter", "-n", memoryName, bewsFiles[files], NULL);
      _exit(EXIT_SUCCESS);
    }else{
      close(link[1]);
      int nbytes = read(link[0], in, sizeof(in));
      printf("\n%.*s ", nbytes, in);
      waitpid(processes[files], &status, 0);
    }
  }
  return 0;
}
