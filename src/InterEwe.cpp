//InterEwe.cpp
#include "InterEwe.h"

InterEwe::InterEwe(char** argvs) : argv(argvs) {
  cout << "InterEwe Object is being created" << endl;
}
InterEwe::~InterEwe(void) {
  cout << "InterEwe Object is being deleting" << endl;  
}
int InterEwe::readBew(char* shmname, int file) {
  fstream myReadFileBew(argv[file],ios_base::binary|ios_base::in);
  int input;
  if (myReadFileBew.is_open()) {
    //while (!myReadFileBew.eof()) {
    while (myReadFileBew.read((char*)&input,sizeof(int))) {
      //myReadFileBew.read((char*)&input,sizeof(int));
      cout << "Bew: " << input << endl;
    }
  }
  myReadFileBew.close();
  assignMemory(shmname);
  
  return 0;
}
int InterEwe::assignMemory(char* shmname) {
  int shm = shm_open(shmname, O_RDWR , 0600);
  off_t size_mem= 1000;
  pMemg = static_cast<char*>(mmap(NULL, size_mem, PROT_READ | PROT_WRITE, MAP_SHARED, shm, 0));
    
  if ((void *) pMemg == (void *) -1) {
    cerr << "Problems with memory map" << endl;
    return 1;
  }
  cout << "Shared memory already assigned"  << endl;
  return 0;
}
