#include <iostream>
#include <iomanip> //hex
#include <fstream> //leer
#include <vector> //borrar vector y todo lo que no sirva

#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

using namespace std;

unsigned char *pMem,*pLitStr, *pDataStr;
unsigned int *pMemg,*pLitNum, *pDataNum, *pWorkLoad; 

//borrar cuando no se use
vector<unsigned long long> instructions;
vector<unsigned char> opcodes;

off_t size_mem;



unsigned int getBase(unsigned int addr){
  return ((addr >> 16) << 2);
}

unsigned int getSize(unsigned int addr){
  return (addr & 0xFFFF);
}

int  assignMemory(char* shmname) {
  int shm = shm_open(shmname, O_RDWR , 0600);
  off_t size_mem= 1000;
  pMem = static_cast<unsigned char*>(mmap(NULL, size_mem, PROT_READ | PROT_WRITE, MAP_SHARED, shm, 0));
    
  if ((void *) pMem == (void *) -1) {
    cerr << "Problems with memory map" << endl;
    return 1;
  }
  cout << "Shared memory already assigned"  << endl;
  pMemg = (unsigned int *)pMem;
  return 0;
}

int main(int argc, char** argv){
    fstream myReadFileBew(argv[3],ios_base::binary|ios_base::in);
    int cont = 0,code;
    unsigned long long addr;
    unsigned char input,opcode,op;
    unsigned short memref, intAddr, strAddr,src,dest,oper1Addr,oper2Addr,mrSize;
    unsigned int oper1, oper2;
    bool dataNum; // 1 = palabra(32 bits), 0 = char (8 bits)
    
    assignMemory(argv[2]);
    
    
    // unsigned int *base = ;
    pLitNum = (unsigned int *)(pMem + getBase(*(pMemg+1)));
    pLitStr = (unsigned char *)(pMem + getBase(*(pMemg+2))); //Char
    pDataNum = (unsigned int *)(pMem + getBase(*(pMemg+3)));
    pDataStr = (unsigned char *)(pMem + getBase(*(pMemg+4))); //Char
    pWorkLoad = (unsigned int *)(pMem + getBase(*(pMemg+5)));

    
    if (myReadFileBew.is_open()){
        while (myReadFileBew.read((char*)&input,sizeof(unsigned char))) {   
            cont++;
            cout <<"instrucción: "<<cont<<endl;
            opcode = input >> 4;
            addr = input & 0xF;
            code = opcode;
            switch (opcode) {
                case 0:
                    cout << "op:"<<code<< endl;
                    for(int i=0;i<7;++i){
                        myReadFileBew.read((char*)&input,sizeof(unsigned char));
                        addr <<= 8;
                        addr |= input;
                    }
                    addr >>= 30; //borra pad     
                    break;
                case 1:
                    cout << "op:"<<code<< endl;
                    for(int i=0;i<7;++i){
                        myReadFileBew.read((char*)&input,sizeof(unsigned char));
                        addr <<= 8;
                        addr |= input;
                    }
                    addr >>= 30; //borra pad
                    break;
                case 2:
                    cout << "op:"<<code<< endl;
                    for(int i=0;i<7;++i){
                        myReadFileBew.read((char*)&input,sizeof(unsigned char));
                        addr <<= 8;
                        addr |= input;
                    }  
                    addr >>= 30; //borra pad          
                    break;
                case 3:
                    cout << "op:"<<code<< endl;
                    for(int i=0;i<3;++i){
                        myReadFileBew.read((char*)&input,sizeof(unsigned char));
                        addr <<= 8;
                        addr |= input;
                    }
                    memref = addr >> 13; //borra pad
                    break;
                case 4:
                    cout << "op:"<<code<< endl;
                    for(int i=0;i<7;++i){
                        myReadFileBew.read((char*)&input,sizeof(unsigned char));
                        addr <<= 8;
                        addr |= input;
                    }
                    addr >>= 29 ; //borra pad
                    break;
                case 5:
                    cout << "op:"<<code<< endl;
                    for(int i=0;i<7;++i){
                        myReadFileBew.read((char*)&input,sizeof(unsigned char));
                        addr <<= 8;
                        addr |= input;
                    }
                    addr >>= 11 ; //borra pad
                    break;
                case 6:
                    for(int i=0;i<7;++i){
                        myReadFileBew.read((char*)&input,sizeof(unsigned char));
                        addr <<= 8;
                        addr |= input;
                    }
                    addr >>= 14;
                    break;
                case 7:
                    cout << "op:"<<code<< endl;                          
                    for(int i=0;i<7;++i){
                        myReadFileBew.read((char*)&input,sizeof(unsigned char));
                        addr <<= 8;
                        addr |= input;
                    }               
                    addr >>=14; 
                    break;
                case 8:
                    cout << "op:"<<code<< endl;
                    for(int i=0;i<3;++i){
                        myReadFileBew.read((char*)&input,sizeof(unsigned char));
                        addr <<= 8;
                        addr |= input;
                    }            
                    addr >>= 13;       
                    break;
                case 9:
                    cout << "op:"<<code<< endl;             
                    for(int i=0;i<3;++i){
                        myReadFileBew.read((char*)&input,sizeof(unsigned char));
                        addr <<= 8;
                        addr |= input;
                    }
                    addr >>= 13;      
                    break;
                    
                case 10:
                    cout << "op:"<<code<< endl;
                    for(int i=0;i<7;++i){
                        myReadFileBew.read((char*)&input,sizeof(unsigned char));
                        addr <<= 8;
                        addr |= input;
                    }
                    addr >>= 30; //borra pad                                
                    break;
                case 11:
                    cout << "op:"<<code<< endl;     
                    for(int i=0;i<3;++i){
                        myReadFileBew.read((char*)&input,sizeof(unsigned char));
                        addr <<= 8;
                        addr |= input;
                    }      
                    addr >>= 13;            
                    break;
                case 12:
                    cout << "op:"<<code<< endl;     
                    for(int i=0;i<3;++i){
                        myReadFileBew.read((char*)&input,sizeof(unsigned char));
                        addr <<= 8;
                        addr |= input;
                    }  
                    addr >>= 13;                
                    break;
                case 13:
                    cout << "op:"<<code<< endl;
                    for(int i=0;i<7;++i){
                        myReadFileBew.read((char*)&input,sizeof(unsigned char));
                        addr <<= 8;
                        addr |= input;
                    }
                    addr >>= 11 ; //borra pad
                    break;
                case 14:
                    cout << "op:"<<code<< endl;
                    break;
                case 15:
                    cout << "op:"<<code<< endl;
                    break;
                default:
                    cerr << "Error: opcode no válido"<< endl;
                    break;

            }
            // cout << "address:" <<hex << addr << endl;
            instructions.push_back(addr); //addr sin opcode
            opcodes.push_back(opcode);
        }    
        cout << endl;
        
        for(int i = 0; i<instructions.size();++i){
            code = opcodes[i];
            cout << "opcode "<<hex << code << " ";
            cout << "address "<<hex << instructions[i]<< endl;
        }               
        
        char aux;
        
        for(int i = 0; i<instructions.size();++i){
            opcode = opcodes[i];
            addr = instructions[i];
            code = opcode;
            
            cout << endl <<"op:"<<code<< endl;           
            cout << "address:" <<hex << addr << endl;
            
            switch (opcode) {
                case 0:                                                        
                    intAddr = addr & 0x7FFF;
                    memref =  addr >> 15;
                    cout << "memref:"<<hex<<memref<<endl;
                    cout << "intAddr:"<<hex<<intAddr<<endl;
                    *(pDataNum + memref) = *(pLitNum + intAddr);                    
                    break;
                case 1:                            
                    strAddr = addr & 0x7FFF;
                    memref =  addr >> 15;
                    cout << "memref:"<<hex<<memref<<endl;
                    cout << "strAddr:"<<hex<<strAddr<<endl;

                    aux = *(pLitStr + strAddr);
                    cont = 0;
                    while(aux){
                        *(pDataStr + memref + cont) = aux;
                        cont++;
                        aux = *(pLitStr + strAddr + cont);
                    }
                    break;
                case 2:                
                    intAddr = addr & 0x7FFF;
                    memref =  addr >> 15;

                    cout << "memref:"<<hex<<memref<<endl;
                    cout << "intAddr:"<<hex<<intAddr<<endl;
                    
                    *(pDataNum + memref) = i+*(pLitNum+intAddr);
                    break;
                case 3:                
                    i = *(pDataNum+memref);
                    break;
                case 4:                    
                    src = addr & 0x7FFF;
                    dest = (addr >> 15) & 0x7FFF;
                    dataNum = addr >> 30;
                    
                    if(dataNum){
                        *(pDataNum + dest) = *(pDataNum + src);
                    }else{
                        aux = *(pDataStr + src);
                        cont = 0;
                        while(aux){
                            *(pDataStr + dest + cont) = aux;
                            cont++;
                            aux = *(pDataStr + src + cont);
                        }
                    }

                    break;
                case 5:                                        
                    oper2Addr = addr & 0x7FFF;
                    oper1Addr = (addr >> 15) & 0x7FFF;
                    dest = (addr >> 30) & 0x7FFF;
                    addr >>= 45;
                    dataNum= addr & 1;
                    op = addr >> 1;

                    
                    if(dataNum){
                        oper1 = *(pDataNum + oper1Addr);
                        oper2 = *(pDataNum + oper1Addr);
                        switch(op):

                    }else{

                    }
                    

                    break;  
                case 6:
                    
                    intAddr = addr & 0X7FFF;
                    src = (addr >> 15) & 0X7FFF;
                    dest = (addr>>30) & 0X7FFF;
                    dataNum = addr >> 45;
                    if(dataNum){

                    }else{
                        
                    }
                    break;
                case 7:
                    src= addr & 0X7FFF;
                    intAddr = (addr >> 15) & 0X7FFF;
                    dest = (addr >> 30) & 0X7FFF;
                    dataNum = addr >> 45;
                    if(dataNum){

                    }else{
                        
                    }  
                    break;
                case 8:                
                    memref = addr;
                    break;
                case 9:
                    memref = addr;
                    break;
                case 10:
                    
                    mrSize = addr & 0x7FFF;
                    dest =  addr >> 15;

                    cout << "dest:" << hex << dest << endl;
                    cout << "mrSize:" << hex << mrSize <<endl;
                    // hacer lo que debe hacer
                    break;
                case 11:                    
                    memref = addr;
                    break;
                case 12:                
                    intAddr = addr;
                    break;
                case 13:                                                            
                    intAddr = addr & 0x7FFF;
                    oper2 = (addr>>15) & 0x7FFF;
                    oper1 = (addr>>30) & 0x7FFF;
                    addr >>= 45;
                    dataNum= addr & 1;
                    op = addr >> 1;
                case 14:
                    cout << "op:"<<code<< endl;
                    break;
                case 15:
                    cout << "op:"<<code<< endl;
                    break;
                default:
                    cerr << "Error: opcode no válido"<< endl;
                    break;

            }
        }
    }
    myReadFileBew.close();
    // assignMemory(argv[1]);
    return 0;
}
