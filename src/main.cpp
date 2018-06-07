// ControlEwe.cpp
#include "InterEwe.h"
#include "ControlEwe.h"
//#include <pthread.h>
#include <iostream>

using namespace std;

// Main function for the program
int main(int argc, char** argv){

  ControlEwe Control(&argv[2]);
  InterEwe Inter(&argv[4]);
  
  Control.readMew(); //Read Mew.mew and Create Memory
  int bewFiles = argc;
  int file = 0;
  while(bewFiles > 4){
    Inter.readBew(argv[2], file);
    file++;
    bewFiles--;
  }
  cout << endl << "¡Execution Succeed!" << endl;
  return 0;
}
