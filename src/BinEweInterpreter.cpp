// ControlEwe.cpp
#include "InterEwe.h" //Check Double Include
#include <iostream>

using namespace std;
int main(int argc, char** argv){

  InterEwe Inter;
  Inter.readBew(argv[2], argv[3]);
  //cout << endl << "¡Interpreter Execution Succeed!" << endl;
  return 0;
}
