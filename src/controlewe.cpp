#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>

#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

using namespace std;

char *pMemg;
int *pLitNum; 
char *pLitStr;
int *pDataNum;
char *pDataStr;
int *pWorkLoad;
off_t size_mem;

int createMemory(char* shmname){

  int shm = shm_open(shmname, O_CREAT | O_RDWR | O_EXCL, 0600);
  if (shm == -1) {
    cerr << "Shared memory already created" << endl;
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

int main(int argc, char** argv){
  if(argc <= 3){
    cerr << "Usage: " << argv[0] << " <MemoryName> ID.mew (ID.bew)+ " << endl;
    return 1;
  }

  int input, Segments = 0, segSize;
  int memorySegments[6];
  fstream myReadFileMew(argv[2],ios_base::binary|ios_base::in);
  if (myReadFileMew.is_open()) {
    while (!myReadFileMew.eof()) {
      myReadFileMew.read((char*)&input,sizeof(int));
      if(Segments <= 5){
        // cout << "~ " << hex <<input << endl;        
        segSize = input & 0x0000FFFF; // sacamos los 4 bits de la derecha
        input >>= 16; //sacamos los 4 bits de la izquierda (correrlo 16 bits)
        input <<= 2; // multiplicamos por 2^2 
        // cout << "desde " << input<< endl;
        // cout << "tamaño " << segSize<< endl;
        if(Segments == 2 || Segments == 4){ //solo si es litstr o .datastr
          if((segSize%4)!= 0 ){
            // cout << "size no es multiplo de 4 "<< segSize << endl;
            segSize = segSize-(segSize%4)+4; // no funciona con -=
          // cout << "multiplo de 4 " << segSize<< endl;
            
          }
        }else{
          segSize <<= 2;    //se corre o no? se daña cuando es con string
          // cout << "multiplicado por 4 " << segSize<< endl;
        }

        // cout << "hasta " << hex << (input+segSize) << endl;
        memorySegments[Segments] = input; //guardamos el inicio o el fin
        Segments++;
      }
      // cout << "* " << input << endl;
    }
  }
  size_mem= memorySegments[5]+segSize;

  for(int i = 0;i<Segments;++i){
    cout << "segmento "<< i <<" "<< hex<<memorySegments[i]<<endl;
  }

  // creamos la memoria
  createMemory(argv[1]);
  
  pLitNum = (int *)(pMemg + memorySegments[1]);
  pLitStr = (char *)(pMemg + memorySegments[2]); //Char
  pDataNum = (int *)(pMemg + memorySegments[3]);
  pDataStr = (char *)(pMemg + memorySegments[4]); //Char
  pWorkLoad = (int *)(pMemg + memorySegments[5]);

  // for (;;) {
  //   *(pMemg) = 1;
  //   *(pMemg+1) = 1;
  //   *(pLitNum) = 4;
  //   *(pLitNum+1) = 4;
  //   *(pLitStr) = 'a';
  //   *(pLitStr+1) = 'a';
  //   *(pDataNum) = 16; 
  //   *(pDataStr) = 'A'; 
  //   *(pWorkLoad) = 32;    
  //   sleep(3);
  // }
  
  cout << endl;
  myReadFileMew.close();
  int bewFile =3; //Argument 3 -> After Memory Name
  int argcs = argc;
  while(argcs > 3){
    fstream myReadFileBew(argv[bewFile],ios_base::binary|ios_base::in);
    if (myReadFileBew.is_open()) {
      while (!myReadFileBew.eof()) {
	myReadFileBew.read((char*)&input,sizeof(int));
	cout << input << endl;
      }
    }
    bewFile++;
    argcs--;
    myReadFileBew.close();
  }
  cout << endl << "¡Execution Succeed!" << endl;
  return 0;
}
