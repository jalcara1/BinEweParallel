// BinEweControl.cpp
#include "ControlEwe.h"
#include <sys/wait.h>
#include <unistd.h>
#include <iostream>

using namespace std;
int main(int argc, char** argv){
  int BinEwe = (argc - 4);
     
  ControlEwe Control(&argv[2]);
  Control.readMew(); //Read Mew.mew and Create Memory

  pid_t processes[BinEwe]; // Run With Exec -> As a Bash Command
  for(int files =0; files< BinEwe; ++files){
    if ((processes[files] = ::fork()) == -1) {
      perror("Exec Process Failed");
      exit(EXIT_FAILURE);
    }else if(processes[files] == 0){
      //cout << "Child: " << processes[files]  << endl;
      //Inter.readBew(argv[2], files);
      execlp( "./BinEweInterpreter", "./BinEweInterpreter", "-n", argv[2], argv[files+4], NULL);
      _exit(EXIT_SUCCESS);
    }else{
      //cout << "Father: " << processes[files]  << endl;
      cout << "Father" << endl;
    }
  }
  int status;
  for(int files =0; files< BinEwe; ++files){
    waitpid(processes[files], &status, 0);
  }
  cout << endl << "¡Control Execution Succeed!" << endl;
  return 0;
}
