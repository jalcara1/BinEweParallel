//ControlEwe.cpp
#include "ControlEwe.h"

ControlEwe::ControlEwe(char** argvs) : argv(argvs)  {
  cout << "ControlEwe Object is being created" << endl;
}
ControlEwe::~ControlEwe(void) {
  cout << "ControlEwe Object is being deleting" << endl;
}
int ControlEwe::readMew() {
  int input, Segments = 0, segSize;
  int memorySegments[6];
  fstream myReadFileMew(argv[1],ios_base::binary|ios_base::in);
  if (myReadFileMew.is_open()) {
    while (myReadFileMew.read((char*)&input,sizeof(int))){//!myReadFileMew.eof()) {
      //myReadFileMew.read((char*)&input,sizeof(int));
      if(Segments <= 5){
        segSize = input & 0x0000FFFF; // sacamos los 4 bits de la derecha
        input >>= 16; //sacamos los 4 bits de la izquierda (correrlo 16 bits)
        input <<= 2; // multiplicamos por 2^2 
        cout << "desde " << input<< endl;
        if(Segments == 2 || Segments == 4){ //solo si es litstr o .datastr
          if((segSize%4)!= 0 ){
            segSize = segSize-(segSize%4)+4; // no funciona con -=
          }
        }else{
          segSize <<= 2;
        }
        memorySegments[Segments] = input; //Saved segments end and start
        cout << Segments << ":"<< hex << input << endl;
        Segments++;
      }
    }
  }
  size_mem= memorySegments[5]+segSize;
  
  for(int i = 0;i<Segments;++i){
    cout << "segmento "<< i <<" "<<memorySegments[i]<<endl;
  }
  createMemory(argv[0]); //Memory Creating
  
  pLitNum = (int *)(pMemg + memorySegments[0]);
  pLitStr = (char *)(pMemg + memorySegments[1]); //Char
  pDataNum = (int *)(pMemg + memorySegments[2]);
  pDataStr = (char *)(pMemg + memorySegments[3]); //Char
  pWorkLoad = (int *)(pMemg + memorySegments[4]);

  myReadFileMew.close();

  return 0;
}
int ControlEwe::createMemory(char* shmname){ //Just Create The *pMem for Each InterEwe
  int shm = shm_open(shmname, O_CREAT | O_RDWR | O_EXCL, 0600);
  if (shm == -1) {
    cerr << "Shared memory already created" << endl;
    // $ man shm_open # Read Manual
    return 1;
  }
  size_mem= 1000; // Workload -> Memory last size
  if (ftruncate(shm, size_mem) == -1) {
    cerr << "Problems with memory size" << endl;
    return 1;
  }
  pMemg = static_cast<char*>(mmap(NULL, size_mem, PROT_READ | PROT_WRITE, MAP_SHARED, shm, 0));
  if ((void *) pMemg == (void *) -1) {
    cerr << "Problems with memory map" << endl;
    return 1;
  }
  return 0;
}
