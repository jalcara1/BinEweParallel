//ControlEwe.h
#ifndef __ControlEwe_H_INCLUDED__   // if x.h hasn't been included yet...
#define __ControlEwe_H_INCLUDED__   // #define this so the compiler knows it has been included

#include "Include.h"
class ControlEwe {
 public:
  int readMew();
  int createMemory(char* shmname);
  unsigned int getSize(unsigned int addr);
  unsigned int getBase(unsigned int addr);

  ControlEwe(char** argv); // This is the constructor declaration
  ~ControlEwe(); // This is the destructor: declaration
 private:
  char** argv;

  off_t size_mem; // Include Specific Library
  unsigned char *pMem;
  unsigned int *pMemg;
  unsigned int *pLitNum; 
  unsigned char *pLitStr;
  unsigned int *pDataNum;
  unsigned char *pDataStr;
  sem_t *pWorkLoad; //Semaphore Type
};

#endif 
