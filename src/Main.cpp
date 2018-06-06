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

int *pMemg;
int *pLitNum; 
char *pLitStr;
int *pDataNum;
char *pDataStr;
int *pWorkLoad;

int createMemory(char* shmname){

  int shm = shm_open(shmname, O_CREAT | O_RDWR | O_EXCL, 0600);
  if (shm == -1) {
    cerr << "Shared memory already created" << endl;
    return 1;
  }
  off_t size_mem = 1000; // Workload -> Memory last size
  if (ftruncate(shm, size_mem) == -1) {
    cerr << "Problems with memory size" << endl;
    return 1;
  }
  char *pMem = static_cast<char*>(mmap(NULL, size_mem, PROT_READ | PROT_WRITE, MAP_SHARED, shm, 0));
  if ((void *) pMem == (void *) -1) {
    cerr << "Problems with memory map" << endl;
    return 1;
  }
  // int *pMemg;
  // int *pLitNum; 
  // char *pLitStr;
  // int *pDataNum;
  // char *pDataStr;
  // int *pWorkLoad;

  int limInf, limSup;
  string number,number2;
  
  //cambiar todo por los segmentos que son
  // int hexa,hexa2;
  
  // while(cin >> setw(2) >> number){
  //   cin >> number;
  //   stringstream  converter(number);
  //   converter >> hex >> hexa;
    
  //   cin >> setw(2) >> number2;
  //   cin >> number2;
  //   stringstream  converter2(number2);
  //   converter2 >> hex >> hexa2;
  //   hexa2 <<= 2;
    
  //   cout << hex << hexa << endl;
  //   cout << hex << hexa2 << endl;
    
  //   if((hexa2%4)!= 0 ){
  //     hexa2= hexa2-(hexa2%4)+4;
  //     cout << " 2 no era multiplo " << hex << hexa2 << endl;
  //   }
  //   cout << "limite " <<hex << hexa+hexa2 << endl;
  // }
  return 0;
}
int main(int argc, char** argv){
  if(argc <= 3){
    cerr << "Usage: " << argv[0] << " <MemoryName> ID.mew (ID.bew)+ " << endl;
    return 1;
  }
  //createMemory(argv[1]);
  int input, Segments = 0, segSize;
  int memorySegments[6];
  fstream myReadFileMew(argv[2],ios_base::binary|ios_base::in);
  if (myReadFileMew.is_open()) {
    while (!myReadFileMew.eof()) {
      myReadFileMew.read((char*)&input,sizeof(int));
      if(Segments <= 5){
        // cout << "~ " << input << endl;
        segSize = input & 0x0000FFFF; // sacamos los 4 bits de la derecha
        input >>= 16; //sacamos los 4 bits de la izquierda (correrlo 16)
        input <<= 2; // multiplicamos por 2^2 
        cout << "desde " << input<< endl;
        
        if(Segments == 2 || Segments == 4){ //solo si es litstr o .datastr
          if((segSize%4)!= 0 ){
            cout << "size no es multiplo de 4 "<< segSize << endl;
            segSize -= (segSize%4)+4; // no funciona con -=
          }
        }
        segSize <<=2;    //se corre o no? se daña cuando es con string
        
        // cout << "hasta " << hex << (input+segSize) << endl;
        memorySegments[Segments] = (input+segSize); //guardamos el inicio o el fin
        cout << "limite " << hex << memorySegments[Segments] << endl;
        Segments++;
      }
      // cout << "* " << input << endl;
    }
  }



  //Assign Correct Value
  cout << " AQUI " << memorySegments[0]  << endl;
  // *pMemg = memorySegments[0];
  // *pLitNum = memorySegments[1];
  // *pLitStr = memorySegments[2]; //Char
  // *pDataNum = memorySegments[3];
  // *pDataStr = memorySegments[4]; //Char
  // *pWorkLoad = memorySegments[5];

  // cout << "- " << *pMemg;
  // cout << "\n-- " << *pLitNum;
  // cout << "\n--- " << *pLitStr;
  // cout << "\n---- " << *pDataNum;
  // cout << "\n----- " << *pDataStr;
  // cout << "\n------ " << *pWorkLoad;
  
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
