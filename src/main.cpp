// ControlEwe.cpp
#include "InterEwe.h"
#include "ControlEwe.h"
#include <iostream>

using namespace std;

// Main function for the program
int main(int argc, char** argv){
  
  InterEwe Inter((argc-4), &argv[4]);
  ControlEwe Control(&argv[2]);
  
  Inter.readBew();
  Control.readMew();
  return 0;
}
