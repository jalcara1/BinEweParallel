// ControlEwe.cpp
#include "InterEwe.h"
#include "ControlEwe.h"
#include <iostream>

using namespace std;

// Main function for the program
int main(int argc, char** argv){
  
  InterEwe Inter((argc-4), &argv[4]);
  ControlEwe Control(&argv[2]);

  Control.readMew(); //Read Mew.mew and Create Memory
  Inter.readBew();

  return 0;
}
