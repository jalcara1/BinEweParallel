//InterEwe.h
#ifndef __InterEwe_H_INCLUDED__   // if x.h hasn't been included yet...
#define __InterEwe_H_INCLUDED__   // #define this so the compiler knows it has been included

#include "Include.h"
class InterEwe {
 public:
  int readBew(char* shmname, char* file);
  int assignMemory(char* shmname);
  InterEwe(); // This is the constructor declaration
  ~InterEwe(); // This is the destructor: declaration
 private:
  char** argv;

  off_t size_mem;
  unsigned int *pMemg;
  unsigned char *pMem;
  unsigned int *pLitNum;
  unsigned char *pLitStr;
  unsigned int *pDataNum;
  unsigned char *pDataStr;
  //sem_t *pWorkLoad; //Semaphore Type
  unsigned int *pWorkLoad;
};

#endif 
