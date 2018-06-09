//ControlEwe.cpp
#include "ControlEwe.h"

ControlEwe::ControlEwe(char** argvs) : argv(argvs)  {
  cout << "ControlEwe Object is being created" << endl;
}
ControlEwe::~ControlEwe(void) {
  cout << "ControlEwe Object is being deleting" << endl;
}
int ControlEwe::readMew() {

  unsigned int input, segSize;
  unsigned int memg[10][2]; //variable cambiada [segmento][ 0 = inicio][1 = size]
  fstream myReadFileMew(argv[1],ios_base::binary|ios_base::in);
  //manejo de políticas
  // char:
  //  0: lectores
  //  1: escritores
  //  2: bloqueo
  //  3: ninguno
  map<unsigned int,char> mapDataNum;
  map<unsigned int,char> mapDataStr;
  if (myReadFileMew.is_open()) {
    for(int i=0;i<=5;++i){
      myReadFileMew.read((char*)&input,sizeof(int));
      segSize = input & 0xFFFF; // sacamos los 4 bits de la derecha
      input >>= 16; //sacamos los 4 bits de la izquierda (correrlo 16 bits)
      input <<= 2; // multiplicamos por 2^2 
      if(i == 2 || i == 4){ //solo si es litstr o .datastr
        if((segSize%4)!= 0 ){
          segSize = segSize-(segSize%4)+4; // no funciona con -=
        }
      }else{
        segSize <<= 2;    //se corre o no? se daña cuando es con string
      }
      memg[i][0] = input; //guardamos el inicio del segmento
      memg[i][1] = segSize; //guardamos el tamaño del segmento
    }
    for(int i=6;i<10;++i){
      myReadFileMew.read((char*)&input,sizeof(int));
      segSize = input & 0xFFFF; // sacamos los 4 bits de la derecha
      input >>= 16; //sacamos los 4 bits de la izquierda (correrlo 16 bits)

      memg[i][0] = input; //guardamos politicas gestion
      memg[i][1] = segSize-input; //guardamos tamaño de la politica
    }
    for(int i = 0;i<10;++i){
      cout << "seg:"<< i <<" ini:"<< hex <<memg[i][0]<<" tam: "<<memg[i][1]<<endl;  
    }
    size_mem= memg[5][0]+memg[5][1]; //Tamaño de la memoria = ultima posicion de WorkLoad
    createMemory(argv[0]); // creamos la memoria
    
    pLitNum = (int *)(pMemg + memg[1][0]);
    pLitStr = (char *)(pMemg + memg[2][0]); //Char
    pDataNum = (int *)(pMemg + memg[3][0]);
    pDataStr = (char *)(pMemg + memg[4][0]); //Char
    pWorkLoad = (sem_t*)(int *)(pMemg + memg[5][0]);
    
    //almacenar los de las políticas
    for(int i = 6 ; i < 10;++i){  
      for(int j = 0; j < memg[i][1] ; ++j){     
        myReadFileMew.read((char*)&input,sizeof(int));
	segSize = input & 0x0000FFFF; // sacamos los 4 bits de la derecha
        input >>= 16; //sacamos los 4 bits de la izquierda (correrlo 16 bits)
	if(input >> 15 == 1){
          //datanum
          input &= 0x1000;
          segSize &= 0x1000;
          for(int k = input; k <= segSize; ++k ){
            mapDataNum[k]=i%6; //se guarda la posicion sin salto
	    //cout <<"datanum =>"<<(int)mapDataNum[k] << endl;
          }
        }else{
          //datastring      
          for(int k = input; k <= segSize; ++k ){
            mapDataStr[k]=i%6; //se guarda la posicion en datanum
	    //cout <<"datastr =>"<<(int)mapDataStr[k] << endl;
          }
        }
      }
    }
  }
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
  //size_mem= 1000; // Workload -> Memory last size
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
