//ControlEwe.h
#ifndef __ControlEwe_H_INCLUDED__   // if x.h hasn't been included yet...
#define __ControlEwe_H_INCLUDED__   // #define this so the compiler knows it has been included

class ControlEwe {

 public:
  int readMew();
  int createMemory(char* shmname);
  ControlEwe(char** argv); // This is the constructor declaration
  ~ControlEwe(); // This is the destructor: declaration
  
 private:
  char** argv;
  
  char *pMemg;
  int *pLitNum; 
  char *pLitStr;
  int *pDataNum;
  char *pDataStr;
  int *pWorkLoad;
  //off_t *size_mem;

};

#endif 
