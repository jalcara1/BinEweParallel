//ControlEwe.cpp
#include "ControlEwe.h"
#include "Include.h"

ControlEwe::ControlEwe(char** argvs) : argv(argvs)  {
  cout << "ControlEwe Object is being created" << endl;
}
ControlEwe::~ControlEwe(void) {
  cout << "ControlEwe Object is being deleting" << endl;
}
int ControlEwe::readMew() {
  cout << "argv[0] --> " << argv[0] << endl;
  cout << "argv[1] --> " << argv[1] << endl;
  return 0;
}


