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

int main(int argc, char** argv){
    if(argc != 2){
    cerr << "Usage control: <shmname>" << endl;
    return 1;
  }
  
  int shm = shm_open(argv[1], O_CREAT | O_RDWR | O_EXCL, 0600);

  if (shm == -1) {
    cerr << "Shared memory already created" << endl;
    return 1;
  }

  off_t size_mem = 1000;

  if (ftruncate(shm, size_mem) == -1) {
    cerr << "Problems with memory size" << endl;
    return 1;
  }

  char *pMem = static_cast<char*>(mmap(NULL, size_mem, PROT_READ | PROT_WRITE,
                                       MAP_SHARED, shm, 0));

  if ((void *) pMem == (void *) -1) {
    cerr << "Problems with memory map" << endl;
    return 1;
  }

  int *pMemg = (int *)pMem;
  int *pLitNum; 
  char *pLitStr;
  int *pDataNum;
  int *pWorkL;

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