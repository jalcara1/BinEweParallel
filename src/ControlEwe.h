//ControlEwe.h
#ifndef __ControlEwe_H_INCLUDED__   // if x.h hasn't been included yet...
#define __ControlEwe_H_INCLUDED__   // #define this so the compiler knows it has been included

#include "Include.h"
class ControlEwe {
 public:
  int readMew();
  int createMemory(int size_mem);
  int getSize(int addr);
  int getBase(int addr);

  ControlEwe(char* shmname, string mewFile); // This is the constructor declaration
  ~ControlEwe(); // This is the destructor: declaration
 private:
  char* shmname;
  string mewFile;

  off_t size_mem; // Include Specific Library
  char *pMem;
  unsigned int *pMemg;
  int *pLitNum; 
  char *pLitStr;
  int *pDataNum;
  char *pDataStr;
  sem_t *pWorkLoad; //Semaphore Type
};

#endif 
