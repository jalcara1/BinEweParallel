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

#include <stdio.h>
#include <algorithm>
#include <iterator>
#include <vector>

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

    unsigned char opcode;
    unsigned long long addr;
    unsigned char input,aux;
    unsigned short memref, intAddr;
    
    if (myReadFileBew.is_open()){
        while (myReadFileBew.read((char*)&input,sizeof(unsigned char))) {   
            // cout << hex <<input << endl;
            opcode = input >> 4;
            addr = input & 0xF;
            switch (opcode) {
                case 0:
                    cout << "op: 0000" << endl;
                    for(int i=0;i<7;++i){
                        myReadFileBew.read((char*)&aux,sizeof(unsigned char));
                        addr <<= 8;
                        addr |= aux;
                    }
                    // printf("mem address: %#08x\n",addr);
                    cout << "address 64:" <<hex << addr << endl;
                    addr >>= 30; //borra pad
                    memref =  addr >> 15;
                    intAddr = addr & 0x7fff;

                    cout << "memref:"<<hex<<memref<<endl;
                    cout << "intAddr:"<<hex<<intAddr<<endl;
                    // hacer lo que debe hacer
                    break;
                case 1:
                    // cout << "op: 0001" << endl;
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
                case 5:
                    break;
                case 6:
                    break;
                case 7:
                    break;
                case 8:
                    break;
                case 9:
                    break;
                case 10:
                    break;
                default:
                    break;

            }
        }
    }
    myReadFileBew.close();
    // assignMemory(argv[1]);
    return 0;
}
