//InterEwe.cpp
#include "InterEwe.h"
#include "Include.h"

InterEwe::InterEwe(int argcs, char** argvs) : argc(argcs), argv(argvs)  {
  cout << "InterEwe Object is being created" << endl;
}
InterEwe::~InterEwe(void) {
  cout << "InterEwe Object is being deleting" << endl;
}
int InterEwe::readBew() {
  cout << "argc --> " << argc << endl;
  cout << "argv --> " << argv[0] << endl;
  return 0;
}


