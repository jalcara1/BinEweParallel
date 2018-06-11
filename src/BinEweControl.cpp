// BinEweControl.cpp
#include "ControlEwe.h"
#include <sys/wait.h>
#include <unistd.h>
//#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
int main(int argc, char** argv){
  int BinEwe = (argc - 4);
  int link[2], status;
  char foo[4096];
  if(pipe(link) == -1){
    exit(EXIT_FAILURE);
  }     
  ControlEwe Control(&argv[2]);
  Control.readMew(); //Read Mew.mew and Create Memory

  pid_t processes[BinEwe]; // Run With Exec -> As a Bash Command
  for(int files =0; files< BinEwe; ++files){
    if ((processes[files] = ::fork()) == -1) {
      perror("Exec Process Failed");
      exit(EXIT_FAILURE);
    }else if(processes[files] == 0){
      dup2(link[1], STDOUT_FILENO);
      close(link[0]);
      close(link[1]);
      execlp( "./BinEweInterpreter", "./BinEweInterpreter", "-n", argv[2], argv[files+4], NULL);
      _exit(EXIT_SUCCESS);
    }else{
      close(link[1]);
      int nbytes = read(link[0], foo, sizeof(foo));
      printf("\n%.*s ", nbytes, foo);
      waitpid(processes[files], &status, 0);
    }
  }
  // int status;
  // for(int files =0; files< BinEwe; ++files){
  //   waitpid(processes[files], &status, 0);
  // }
  //cout << endl << "¡Control Execution Succeed!" << endl;
  return 0;
}
