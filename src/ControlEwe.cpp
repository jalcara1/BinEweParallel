//Controlewe.cpp
#include "ControlEwe.h"

ControlEwe::ControlEwe(char* shmname, string mewFile) : shmname(shmname), mewFile(mewFile) {
  //cout << "ControlEwe Object is being created" << endl;
}
ControlEwe::~ControlEwe(void) {
  //cout << "ControlEwe Object is being deleted" << endl;
}
int ControlEwe::readMew() {
  int segSize;
  unsigned int input,segments[6] ;
  char leer;

  fstream myReadFileMew(mewFile,ios_base::binary|ios_base::in);
 
  if (myReadFileMew.is_open()) {  
    for(int i = 0; i <= 5; ++i){
      myReadFileMew.read((char*)&input,sizeof(unsigned int));
      segments[i] = input;
    }
    // calcular tamaño memoria
    size_mem = getBase(segments[5]) + getSize(segments[5]);  // inicio workload + tamaño
  
    if(createMemory(size_mem)){ // crear memoria
      cerr << "Error: la memoria "<<shmname<<" ha creada anteriormente"<<endl;
      return 1;
    }
    
    pMemg = (unsigned int *)(pMem+0);
    
    for(int i = 0; i <= 5; ++i){
      input = segments[i];      
      if(i == 2 || i == 4){ //solo si es litstr o .datastr
        if( (input%4) != 0 ){
          input = input-(input%4)+4;
        }
      }
      *(pMemg + i) = input;
    }
    pLitNum = (int *)(pMem + getBase(*(pMemg+1)));
    pLitStr = (char *)(pMem + getBase(*(pMemg+2))); //Char
    pDataNum = (int *)(pMem + getBase(*(pMemg+3)));
    pDataStr = (char *)(pMem + getBase(*(pMemg+4))); //Char
    pWorkLoad = (sem_t*)((int *)(pMem + getBase(*(pMemg+5))));

    segSize = getSize(int(*(pMemg + 0))); // .memg size    
    
    for(int i = 6; i < segSize; ++i){
      myReadFileMew.read((char*)&input,sizeof(unsigned int));
      *(pMemg + i) = input;
    }
    segSize =  getSize(int(*(pMemg+1)));
    // escribir litnum
    for(int i = 0; i < segSize ; ++i){
      myReadFileMew.read((char*)&input,sizeof(unsigned int));
      *(pLitNum+i) = input;     
    }
    segSize =  getSize(int(*(pMemg+2)));
    // escribir litstring
    for(int i = 0; i< segSize; ++i){
      myReadFileMew.read((char*)&leer,sizeof(char));
      *(pLitStr+i) = leer;
    }
    // int sem_init(sem_t *sem, int pshared, unsigned int value);
    // If pshared is nonzero, then the semaphore is shared between processes, and should be located in a region of shared memory
    sem_t mutex1, mutexcescr, slect, sescr, mutex2, mutextlect, mutexB, mutexBImp, mutexInputOutput;
    sem_init(&mutex1, 1, 1);
    sem_init(&mutexcescr, 1, 1);
    sem_init(&slect, 1, 1);
    sem_init(&sescr, 1, 1);
    sem_init(&mutex2, 1, 1);
    sem_init(& mutextlect, 1, 1);
    sem_init(&mutexB, 1, 1);
    sem_init(&mutexBImp, 1, 1);
    sem_init(&mutexInputOutput, 1, 1);
    *(pWorkLoad+0) = mutex1;
    *(pWorkLoad+1) = mutexcescr;
    *(pWorkLoad+2) = slect;
    *(pWorkLoad+3) = sescr;
    *(pWorkLoad+4) = mutex2;
    *(pWorkLoad+5) = mutextlect;
    *(pWorkLoad+6) = mutexB;
    *(pWorkLoad+7) = mutexBImp;
    *(pWorkLoad+8) = mutexInputOutput;
  }
  myReadFileMew.close();
  return 0;
}

int ControlEwe::createMemory(int size_mem){ //Just Create The *pMem for Each InterEwe
  // size_mem = 1000;/
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
  pMem = static_cast<char*>(mmap(NULL, size_mem, PROT_READ | PROT_WRITE, MAP_SHARED, shm, 0));
  if ((void *) pMem == (void *) -1) {
    cerr << "Problems with memory map" << endl;
    return 1;
  }
  cout << "Memoria creada"<<endl;
  return 0;
}
int ControlEwe::getSize(int addr){
  return (addr & 0xFFFF);
}
int ControlEwe::getBase(int addr){
  return ((addr >> 16) << 2);
}
