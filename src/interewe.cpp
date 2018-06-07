#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>

#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#include <map>
#include "InterEwe.h"

using namespace std;

char *pMemg;
int *pLitNum; 
char *pLitStr;
int *pDataNum;
char *pDataStr;
int *pWorkLoad;
off_t size_mem;

int  assignMemory(char* shmname) {
  int shm = shm_open(shmname, O_RDWR , 0600);
  off_t size_mem= 1000;
  pMemg = static_cast<char*>(mmap(NULL, size_mem, PROT_READ | PROT_WRITE, MAP_SHARED, shm, 0));
    
  if ((void *) pMemg == (void *) -1) {
    cerr << "Problems with memory map" << endl;
    return 1;
  }
  cout << "Shared memory already assigned"  << endl;
  return 0;
}

int main(int argc, char** argv){
    fstream myReadFileBew(argv[2],ios_base::binary|ios_base::in);
    int cont=0;
    int opcode,memAdr,intAdr;
    unsigned char input;
    if (myReadFileBew.is_open()) {
        //while (!myReadFileBew.eof()) {
        while (myReadFileBew.read((char*)&input,sizeof(unsigned char))) {
            //myReadFileBew.read((char*)&input,sizeof(int));
            // cout<<hex<<input<<" ";
            opcode = input >> 4;
            cout << opcode ;
            switch (opcode) {
                case 0:
                    myReadFileBew.read((char*)&input,sizeof(unsigned char))
                break;
                case c:
                // Code
                break;
                default:
                // Code
                break;
            }


            cout<<hex<<input << endl;
        
            
        }
    }
    myReadFileBew.close();
    assignMemory(argv[1]);


    return 0;
}
