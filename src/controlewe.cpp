#include <iostream>
#include <iomanip>
#include <fstream>

#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#include <map>

using namespace std;

unsigned char *pMem,*pLitStr, *pDataStr;
unsigned int *pMemg,*pLitNum, *pDataNum, *pWorkLoad; 

off_t size_mem;

int createMemory(char* shmname){
  size_mem = 1000;
  int shm = shm_open(shmname, O_CREAT | O_RDWR | O_EXCL, 0600);
  if (shm == -1) {
    cerr << "Shared memory already created" << endl;
    return 1;
  }
  if (ftruncate(shm, size_mem) == -1) {
    cerr << "Problems with memory size" << endl;
    return 1;
  }
  pMem = static_cast<unsigned char*>(mmap(NULL, size_mem, PROT_READ | PROT_WRITE, MAP_SHARED, shm, 0));
  if ((void *) pMem == (void *) -1) {
    cerr << "Problems with memory map" << endl;
    return 1;
  }
  pMemg = (unsigned int *)pMem;
  return 0;
}

int getSize(unsigned int addr){
  return (addr & 0xFFFF);
}

int getBase(unsigned int addr){
  return ((addr >> 16) << 2);
}

int main(int argc, char** argv){
  
  if(argc <= 3){
    cerr << "Usage: " << argv[0] << " <MemoryName> ID.mew (ID.bew)+ " << endl;
    return 1;
  }

  unsigned int input, memgSize;
  unsigned char leer;
  // unsigned int memg[10][2]; //variable cambiada [segmento][ 0 = inicio][1 = size]
  fstream myReadFileMew(argv[2],ios_base::binary|ios_base::in);
  
  if (myReadFileMew.is_open()) {
    myReadFileMew.read((char*)&input,sizeof(unsigned int));
    
    memgSize = getSize(input); // tamaño de memg
    unsigned int memg[memgSize]; 
    memg[0] = input; 
    
    for(int i = 1;i<memgSize;++i){
      myReadFileMew.read((char*)&input,sizeof(unsigned int));
      memg[i] = input;
    }

    // calcular tamaño memoria
    input = memg[5];
    size_mem = getBase(input)+ getSize(input);  // inicio workload + tamaño
    
    
    if(createMemory(argv[1])){ // crear memoria
      cerr << "Error: la memoria "<<argv[1]<<" ha creada anteriormente"<<endl;
      return 1;
    }

    // escribir en memoria
    for(int i = 0;i<memgSize;++i){
      *(pMemg+i) = memg[i];
    }


    cout << getBase(memg[1]) << endl;
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
}
