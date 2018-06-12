//Controlewe.cpp
#include "ControlEwe.h"

ControlEwe::ControlEwe(char** argvs) : argv(argvs)  {
  //cout << "ControlEwe Object is being created" << endl;
}
ControlEwe::~ControlEwe(void) {
  //cout << "ControlEwe Object is being deleted" << endl;
}
int ControlEwe::readMew() {
  unsigned int input, memgSize;
  unsigned char leer;
  fstream myReadFileMew(argv[1],ios_base::binary|ios_base::in);
  if (myReadFileMew.is_open()) {
    myReadFileMew.read((char*)&input,sizeof(unsigned int));
    memgSize = getSize(input); // .memg size
    if(createMemory(argv[0])){ // crear memoria
      cerr << "Error: la memoria "<<argv[1]<<" ha creada anteriormente"<<endl;
      return 1;
    }
    *(pMemg+0) = input;
    for(int i = 1; i< memgSize; ++i){
      myReadFileMew.read((char*)&input,sizeof(unsigned int));
      *(pMemg + i) = input;
    }
    // calcular tamaño memoria
    input = *(pMemg + 5); //memg[5];
    size_mem = getBase(input) + getSize(input);  // inicio workload + tamaño
    // crear punteros
    pLitNum = (unsigned int *)(pMem + getBase(*(pMemg+1)));
    pLitStr = (unsigned char *)(pMem + getBase(*(pMemg+2))); //Char
    pDataNum = (unsigned int *)(pMem + getBase(*(pMemg+3)));
    pDataStr = (unsigned char *)(pMem + getBase(*(pMemg+4))); //Char
    pWorkLoad = (sem_t*)((int *)(pMem + getBase(*(pMemg+5))));
    // escribir litnum
    for(int i = 0; i< getSize(*(pMemg+1)); ++i){
      myReadFileMew.read((char*)&input,sizeof(unsigned int));
      *(pLitNum+i) = input;
    }
    // escribit litstring
    for(int i = 0; i< getSize(*(pMemg+2)); ++i){
      myReadFileMew.read((char*)&leer,sizeof(unsigned char));
      *(pLitStr+i) = leer;
    }
    // int sem_init(sem_t *sem, int pshared, unsigned int value);
    // If pshared is nonzero, then the semaphore is shared between processes, and should be located in a region of shared memory
    sem_t mutex;
    sem_init(&mutex, 1, 1);
    *(pWorkLoad+0) = mutex;
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
unsigned int ControlEwe::getSize(unsigned int addr){
  return (addr & 0xFFFF);
}
unsigned int ControlEwe::getBase(unsigned int addr){
  return ((addr >> 16) << 2);
}
