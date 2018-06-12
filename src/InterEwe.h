//InterEwe.h
#ifndef __InterEwe_H_INCLUDED__   // if x.h hasn't been included yet...
#define __InterEwe_H_INCLUDED__   // #define this so the compiler knows it has been included

#include "Include.h"
class InterEwe {
 public:
  int readBew(char* shmname, char* file);
  int assignMemory(char* shmname);
  int assignSections();
  int getBase(int addr);
  int getSize(int addr);
  void writeDatanum(int pos, int data, int politica);
  int readLitNum(int dir);
  char readLitstr(int pos);
  int readDatanum(int pos,int politica);
  char readDatastr(int pos,int politica);
  void writeDatastr(int pos, char data,int politica);
  InterEwe(); // This is the constructor declaration
  ~InterEwe(); // This is the destructor: declaration
 private:
  char** argv;

  off_t size_mem;
  unsigned int *pMemg;
  char *pMem;
  int *pLitNum;
  char *pLitStr;
  int *pDataNum;
  char *pDataStr;
  sem_t *pWorkLoad; //Semaphore Type
};

#endif 
