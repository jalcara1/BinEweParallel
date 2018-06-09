// ControlEwe.cpp
#include "InterEwe.h" //Check Double Include
#include "ControlEwe.h"
#include <iostream>
#include <sys/wait.h>

using namespace std;

// Main function for the program
int main(int argc, char** argv){
  int BinEwe = (argc - 4);
     
  ControlEwe Control(&argv[2]);
  InterEwe Inter(&argv[4]);
  
  Control.readMew(); //Read Mew.mew and Create Memory

  pid_t processes[BinEwe]; // Run With Exec -> As a Bash Command
  for(int file =0; file< BinEwe; ++file){
    if ((processes[file] = ::fork()) == 0) {
      //cout << "Child: " << processes[file]  << endl;
      Inter.readBew(argv[2], file);
      _exit(EXIT_SUCCESS);
    }else{
      //cout << "Father: " << processes[file]  << endl;
    }
  }
  int status;
  for(int file =0; file< BinEwe; ++file){
    waitpid(processes[file], &status, 0);
  }
  cout << endl << "¡Execution Succeed!" << endl;
  return 0;
}
