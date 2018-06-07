//InterEwe.h
#ifndef __InterEwe_H_INCLUDED__   // if x.h hasn't been included yet...
#define __InterEwe_H_INCLUDED__   // #define this so the compiler knows it has been included

#include "Include.h"
class InterEwe {
 public:
  int readBew(char* shmname, int file);
  int assignMemory(char* shmname);
  InterEwe(char** argv); // This is the constructor declaration
  ~InterEwe(); // This is the destructor: declaration
 private:
  char** argv;

  char *pMemg;
  int *pLitNum;
  char *pLitStr;
  int *pDataNum;
  char *pDataStr;
  //int *pWorkLoad; //Type
};

#endif 
