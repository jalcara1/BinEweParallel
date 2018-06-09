//Controlewe.cpp
#include "ControlEwe.h"

ControlEwe::ControlEwe(char** argvs) : argv(argvs)  {
  cout << "ControlEwe Object is being created" << endl;
}
ControlEwe::~ControlEwe(void) {
  cout << "ControlEwe Object is being deleting" << endl;
}
int ControlEwe::readMew() {
  unsigned int input, memgSize;
  unsigned char leer;
  fstream myReadFileMew(argv[1],ios_base::binary|ios_base::in);
  if (myReadFileMew.is_open()) {
    myReadFileMew.read((char*)&input,sizeof(unsigned int));
    memgSize = getSize(input); // .memg size
    unsigned int memg[memgSize];
    memg[0] = input;
    for(int i = 1;i<memgSize;++i){
      myReadFileMew.read((char*)&input,sizeof(unsigned int));
      memg[i] = input;
    }
    // calcular tamaño memoria
    input = memg[5];
    size_mem = getBase(input)+ getSize(input);  // inicio workload + tamaño
    if(createMemory(argv[0])){ // crear memoria
      cerr << "Error: la memoria "<<argv[1]<<" ha creada anteriormente"<<endl;
      return 1;
    }
    // escribir en memoria
    for(int i = 0; i< memgSize;++i){
      *(pMemg+i) = memg[i];
    }
    // crear punteros
    pLitNum = (unsigned int *)(pMem + getBase(memg[1]));
    pLitStr = (unsigned char *)(pMem + getBase(memg[2])); //Char
    pDataNum = (unsigned int *)(pMem + getBase(memg[3]));
    pDataStr = (unsigned char *)(pMem + getBase(memg[4])); //Char
    pWorkLoad = (unsigned int *)(pMem + getBase(memg[5]));
    // escribir litnum
    for(int i = 0; i<getSize(memg[1]);++i){
      myReadFileMew.read((char*)&input,sizeof(unsigned int));
      *(pLitNum+i) = input;
    }
    // escribit litstring
    for(int i = 0; i<getSize(memg[2]);++i){
      myReadFileMew.read((char*)&leer,sizeof(unsigned char));
      *(pLitStr+i) = leer;
    }
  }
  myReadFileMew.close();
  return 0;
}
int ControlEwe::createMemory(char* shmname){ //Just Create The *pMem for Each InterEwe
  size_mem = 1000;
  int shm = shm_open(shmname, O_CREAT | O_RDWR | O_EXCL, 0600);
  if (shm == -1) {
    cerr << "Shared memory already created" << endl;
    return 1;
  }    // $ man shm_open # Read Manual
  if (ftruncate(shm, size_mem) == -1) {
    cerr << "Problems with memory size" << endl;
    return 1;
  }
  //size_mem= 1000; // Workload -> Memory last size
  pMem = static_cast<unsigned char*>(mmap(NULL, size_mem, PROT_READ | PROT_WRITE, MAP_SHARED, shm, 0));
  if ((void *) pMem == (void *) -1) {
    cerr << "Problems with memory map" << endl;
    return 1;
  }
  pMemg = (unsigned int *)pMem;
  return 0;
}
int ControlEwe::getSize(int addr){
  return (addr & 0xFFFF);
}
int ControlEwe::getBase(int addr){
  return ((addr >> 16) << 2);
}
