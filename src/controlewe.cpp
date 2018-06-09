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

char *pMemg, *pLitStr, *pDataStr;
int  *pLitNum, *pDataNum, *pWorkLoad; 

off_t size_mem;

int createMemory(char* shmname){

  int shm = shm_open(shmname, O_CREAT | O_RDWR | O_EXCL, 0600);
  if (shm == -1) {
    cerr << "Shared memory already created" << endl;
    return 1;
  }
  if (ftruncate(shm, size_mem) == -1) {
    cerr << "Problems with memory size" << endl;
    return 1;
  }
  char *pMem = static_cast<char*>(mmap(NULL, size_mem, PROT_READ | PROT_WRITE, MAP_SHARED, shm, 0));
  if ((void *) pMem == (void *) -1) {
    cerr << "Problems with memory map" << endl;
    return 1;
  }

  pMemg = pMem;
  return 0;
}

int main(int argc, char** argv){
  
  if(argc <= 3){
    cerr << "Usage: " << argv[0] << " <MemoryName> ID.mew (ID.bew)+ " << endl;
    return 1;
  }

  unsigned int input, segSize;
  unsigned char leer;
  unsigned int memg[10][2]; //variable cambiada [segmento][ 0 = inicio][1 = size]
  fstream myReadFileMew(argv[2],ios_base::binary|ios_base::in);
  
  //manejo de políticas
  // char:
  //  0: lectores
  //  1: escritores
  //  2: bloqueo
  //  3: ninguno
  map<unsigned int,char> mapDataNum;
  map<unsigned int,char> mapDataStr;

  if (myReadFileMew.is_open()) {
    for(int i=0;i<5;++i){
      myReadFileMew.read((char*)&input,sizeof(int));
      
      segSize = input & 0xFFFF; // sacamos los 4 bits de la derecha
      input >>= 16; //sacamos los 4 bits de la izquierda (correrlo 16 bits)
      input <<= 2; // multiplicamos por 2^2 

      if(i == 2 || i == 4){ //solo si es litstr o .datastr
        if((segSize%4)!= 0 ){
          segSize = segSize-(segSize%4)+4; // no funciona con -=
        }
      }
      // else{
      //   segSize <<= 2;    //se corre o no? se daña cuando es con string
      // }
     
      memg[i][0] = input; //guardamos el inicio o el fin
      memg[i][1] = segSize; //guardamos el inicio o el fin
    }
    // workload
    myReadFileMew.read((char*)&input,sizeof(int));
    memg[5][1] = input & 0xFFFF; //guardamos el inicio o el fin
    input >>= 16;
    memg[5][0] = input << 2; 

    for(int i=6;i<=9;++i){
      myReadFileMew.read((char*)&input,sizeof(int));
      segSize = input & 0xFFFF; // sacamos los 4 bits de la derecha
      input >>= 16; //sacamos los 4 bits de la izquierda (correrlo 16 bits)

      memg[i][0] = input; //guardamos el inicio o el fin
      memg[i][1] = segSize-input; //guardamos el inicio o el fin
    }

    // for(int i = 0;i<10;++i){
    //   cout << "seg:"<< i <<" ini:"<< hex <<memg[i][0]<<" tam:"<<memg[i][1]<<"hasta: "<<memg[i][0]+memg[i][1]<<endl;  
    // }
  
    size_mem= memg[5][0]+memg[5][1];

    // creamos la memoria
    int memory = createMemory(argv[1]);
    if(memory){
      cerr << "memoria creada anteriormente"<<endl;
      return 1;
    }
    
    cout << " ini:"<< hex <<memg[1][0]<<endl;
    pLitNum = (int *)(pMemg + memg[1][0]);
    pLitStr = (char *)(pMemg + memg[2][0]); //Char
    pDataNum = (int *)(pMemg + memg[3][0]);
    pDataStr = (char *)(pMemg + memg[4][0]); //Char
    pWorkLoad = (int *)(pMemg + memg[5][0]);

    //almacenar los de las políticas
    int conta = 10;
    for(int i = 6 ; i < 10;++i){  
      for(int j = 0; j < memg[i][1] ; ++j){     
        conta++;
        myReadFileMew.read((char*)&input,sizeof(int));
        
        segSize = input & 0x0000FFFF; // sacamos los 4 bits de la derecha
        input >>= 16; //sacamos los 4 bits de la izquierda (correrlo 16 bits)
        
        if(input >> 15 == 1){
          //datanum
          input &= 0x1000;
          segSize &= 0x1000;
          for(int k = input; k <= segSize; ++k ){
            mapDataNum[k]=i%6; //se guarda la posicion sin salto
            // cout <<"datanum =>"<<(int)mapDataNum[k] << endl;
          }
        }else{
          //datastring      
          for(int k = input; k <= segSize; ++k ){
            // cout << "k: "<<k<<endl;
            mapDataStr[k]=i%6; //se guarda la posicion en datanum
            // cout <<"datastr =>"<<(int)mapDataStr[k] << endl;
          }
        }

      }
    }

    for(int i = 0; i<memg[1][1];++i){
      myReadFileMew.read((char*)&input,sizeof(int));
      *(pLitNum+i) = input;
      conta++;
    }

    for(int i = 0; i<memg[2][1];++i){
      myReadFileMew.read((char*)&leer,sizeof(unsigned char));
      *(pLitStr+i) = leer;
      conta++;
    }
    

  }

  myReadFileMew.close();
  // for (;;) {
    
  //   *(pMemg+1) = 1;
  
  //   *(pLitNum+1) = 4;
  //   *(pLitStr) = 'a';
  //   *(pLitStr+1) = 'a';
  //   *(pDataNum) = 16; 
  //   *(pDataStr) = 'A'; 
  //   *(pWorkLoad) = 32;    
  //   sleep(3);
  // }
  
}
