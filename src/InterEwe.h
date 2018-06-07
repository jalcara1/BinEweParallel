//InterEwe.h
#ifndef __InterEwe_H_INCLUDED__   // if x.h hasn't been included yet...
#define __InterEwe_H_INCLUDED__   // #define this so the compiler knows it has been included

class InterEwe {

 public:
  int readBew();
  InterEwe(int argc, char** argv); // This is the constructor declaration
  ~InterEwe(); // This is the destructor: declaration
 private:
  int argc;
  char** argv;
};

#endif 
