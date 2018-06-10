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
    // unsigned int oper1, oper2, result;
   
//    !!ojo se llamaba data num
//    !!!OJO revisar la logica de los ifs que contienen este boolean
    bool flag; // 1 = palabra(32 bits), 0 = char (8 bits)
    
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
            // cout <<"instrucción: "<<cont<<endl;
            opcode = input >> 4;
            addr = input & 0xF;
            code = opcode;
            switch (opcode) {
                case 0:
                    // cout << "op:"<<code<< endl;
                    for(int i=0;i<7;++i){
                        myReadFileBew.read((char*)&input,sizeof(unsigned char));
                        addr <<= 8;
                        addr |= input;
                    }
                    addr >>= 30; //borra pad     
                    break;
                case 1:
                    // cout << "op:"<<code<< endl;
                    for(int i=0;i<7;++i){
                        myReadFileBew.read((char*)&input,sizeof(unsigned char));
                        addr <<= 8;
                        addr |= input;
                    }
                    addr >>= 30; //borra pad
                    break;
                case 2:
                    // cout << "op:"<<code<< endl;
                    for(int i=0;i<7;++i){
                        myReadFileBew.read((char*)&input,sizeof(unsigned char));
                        addr <<= 8;
                        addr |= input;
                    }  
                    addr >>= 30; //borra pad          
                    break;
                case 3:
                    // cout << "op:"<<code<< endl;
                    for(int i=0;i<3;++i){
                        myReadFileBew.read((char*)&input,sizeof(unsigned char));
                        addr <<= 8;
                        addr |= input;
                    }
                    memref = addr >> 13; //borra pad
                    break;
                case 4:
                    // cout << "op:"<<code<< endl;
                    for(int i=0;i<7;++i){
                        myReadFileBew.read((char*)&input,sizeof(unsigned char));
                        addr <<= 8;
                        addr |= input;
                    }
                    addr >>= 29 ; //borra pad
                    break;
                case 5:
                    // cout << "op:"<<code<< endl;
                    for(int i=0;i<7;++i){
                        myReadFileBew.read((char*)&input,sizeof(unsigned char));
                        addr <<= 8;
                        addr |= input;
                    }
                    addr >>= 11 ; //borra pad
                    break;
                case 6:
                    // cout << "op:"<<code<< endl;                          
                    for(int i=0;i<7;++i){
                        myReadFileBew.read((char*)&input,sizeof(unsigned char));
                        addr <<= 8;
                        addr |= input;
                    }
                    addr >>= 14;
                    break;
                case 7:
                    // cout << "op:"<<code<< endl;                          
                    for(int i=0;i<7;++i){
                        myReadFileBew.read((char*)&input,sizeof(unsigned char));
                        addr <<= 8;
                        addr |= input;
                    }               
                    addr >>=14; 
                    break;
                case 8:
                    // cout << "op:"<<code<< endl;
                    for(int i=0;i<3;++i){
                        myReadFileBew.read((char*)&input,sizeof(unsigned char));
                        addr <<= 8;
                        addr |= input;
                    }            
                    addr >>= 13;       
                    break;
                case 9:
                    // cout << "op:"<<code<< endl;             
                    for(int i=0;i<3;++i){
                        myReadFileBew.read((char*)&input,sizeof(unsigned char));
                        addr <<= 8;
                        addr |= input;
                    }
                    addr >>= 13;      
                    break;
                    
                case 10:
                    // cout << "op:"<<code<< endl;
                    for(int i=0;i<7;++i){
                        myReadFileBew.read((char*)&input,sizeof(unsigned char));
                        addr <<= 8;
                        addr |= input;
                    }
                    addr >>= 30; //borra pad                                
                    break;
                case 11:
                    // cout << "op:"<<code<< endl;     
                    for(int i=0;i<3;++i){
                        myReadFileBew.read((char*)&input,sizeof(unsigned char));
                        addr <<= 8;
                        addr |= input;
                    }      
                    addr >>= 13;            
                    break;
                case 12:
                    // cout << "op:"<<code<< endl;     
                    for(int i=0;i<3;++i){
                        myReadFileBew.read((char*)&input,sizeof(unsigned char));
                        addr <<= 8;
                        addr |= input;
                    }  
                    addr >>= 13;                
                    break;
                case 13:
                    // cout << "op:"<<code<< endl;
                    for(int i=0;i<7;++i){
                        myReadFileBew.read((char*)&input,sizeof(unsigned char));
                        addr <<= 8;
                        addr |= input;
                    }
                    addr >>= 11 ; //borra pad
                    break;
                // los 13 y 14 no harían nada aca            
                default:                
                    break;

            }
            // cout << "address:" <<hex << addr << endl;
            instructions.push_back(addr); //addr sin opcode
            opcodes.push_back(opcode);
        }    
        
        cout <<  endl << "Instrucciones: "<<endl;
        for(int i = 0; i<instructions.size();++i){
            code = opcodes[i];
            cout << "opcode "<<hex << code << " ";
            cout << "address "<<hex << instructions[i]<< endl;
        }               
        
        cout << endl << "Interpretando: "<< endl;
        char aux;       
        for(int PC = 0; PC<instructions.size();++PC){            
            opcode = opcodes[PC];
            addr = instructions[PC];
            code = opcode;
            
            cout << endl << "PC "<<PC<<endl;
            cout <<"op:"<<code<< endl;           
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

                    cont = 0;
                    // aux = *(pLitStr + strAddr + cont)
                    while(*(pLitStr + strAddr + cont)){
                        *(pDataStr + memref + cont) = *(pLitStr + strAddr + cont);
                        cont++;
                    }
                    *(pDataStr + memref + cont) = *(pLitStr + strAddr + cont);
                    break;
                case 2:                
                    intAddr = addr & 0x7FFF;
                    memref =  addr >> 15;

                    cout << "memref:"<<hex<<memref<<endl;
                    cout << "intAddr:"<<hex<<intAddr<<endl;
                    
                    *(pDataNum + memref) = PC+*(pLitNum+intAddr);
                    break;
                case 3:                
                    memref = addr >> 13;
                    PC = *(pDataNum+memref);
                    cout << "memref:"<<hex<<memref<<endl;
                    cout << "PC:"<<hex<<PC<<endl;
                    break;
                case 4:                    
                    src = addr & 0x7FFF;
                    dest = (addr >> 15) & 0x7FFF;
                    flag = addr >> 30;
                    
                    cout << "src:"<< hex << src << endl;
                    cout << "dest:" << hex << dest << endl;
                    cout << "flag:" << hex << flag <<endl;
                    
                    if(flag){
                        *(pDataNum + dest) = *(pDataNum + src);
                    }else{
                        
                        cont = 0;
                        // aux = *(pDataStr + src + cont);
                        while(*(pDataStr + src + cont)){
                            *(pDataStr + dest + cont) = *(pDataStr + src + cont);
                            cont++;                            
                        }
                        *(pDataStr + dest + cont) = *(pDataStr + src + cont);            
                    }                                                  
                    break;
                case 5:                                        
                    oper2Addr = addr & 0x7FFF;
                    oper1Addr = (addr >> 15) & 0x7FFF;
                    dest = (addr >> 30) & 0x7FFF;
                    addr >>= 45;
                    flag= addr & 1;
                    op = addr >> 1;
                    
                    cout << "oper2Addr:" << hex << oper2Addr <<endl;
                    cout << "oper1Addr:" << hex << oper1Addr <<endl;
                    cout << "dest:" << hex << dest <<endl;
                    cout << "flag:" << hex << flag <<endl;
                    cout << "op:" << hex << op <<endl;
                    
                    if(flag){
                        // en caso de que el bit este en 1, las operaciones se hacen en flag
                        // oper1 = *(pDataNum + oper1Addr);
                        // oper2 = *(pDataNum + oper2Addr);
                        switch(op){
                            case 0:
                                // result = oper1 + oper2;
                                *(pDataNum + dest) = *(pDataNum + oper1Addr) + *(pDataNum + oper2Addr); 
                                break;
                            case 1:
                                // result = oper1 - oper2;
                                *(pDataNum + dest) = *(pDataNum + oper1Addr) - *(pDataNum + oper2Addr); 
                                break;
                            case 2:
                                // result = oper1 * oper2;
                                *(pDataNum + dest) = *(pDataNum + oper1Addr) * *(pDataNum + oper2Addr); 
                                break;
                            case 3:
                                // result = oper1 / oper2;
                                *(pDataNum + dest) = *(pDataNum + oper1Addr) / *(pDataNum + oper2Addr); 
                                break;
                            case 4:
                                // result = oper1 % oper2;
                                *(pDataNum + dest) = *(pDataNum + oper1Addr) % *(pDataNum + oper2Addr); 
                                break;
                            default:
                                cerr << "Error: operador no existe "<< endl;
                                return 1;
                        }                
                    }else{
                        // operaciones a nivel de un caracter
                        // oper1 = *(pDataStr + oper1Addr);
                        // oper2 = *(pDataStr + oper2Addr);
                        switch(op){
                            case 0:
                                // result = oper1 + oper2;
                                *(pDataStr + dest) = *(pDataStr + oper1Addr) + *(pDataStr + oper2Addr);
                            case 1:
                                // result = oper1 - oper2;
                                *(pDataStr + dest) = *(pDataStr + oper1Addr) - *(pDataStr + oper2Addr);
                            case 2:
                                // result = oper1 * oper2 ;
                                *(pDataStr + dest) = *(pDataStr + oper1Addr) * *(pDataStr + oper2Addr);
                            case 3:
                                // result = oper1 / oper2;
                                *(pDataStr + dest) = *(pDataStr + oper1Addr) / *(pDataStr + oper2Addr);
                            case 4:
                                // result = oper1 % oper2;
                                *(pDataStr + dest) = *(pDataStr + oper1Addr) % *(pDataStr + oper2Addr);
                        }
                    }
                    
                    break;  
                case 6:                    
                    intAddr = addr & 0X7FFF;
                    src = (addr >> 15) & 0X7FFF;
                    dest = (addr>>30) & 0X7FFF;
                    flag = addr >> 45;
                    if(flag){
                        *(pDataNum + dest) = *(pDataNum + src + intAddr);
                    }else{
                        *(pDataStr + dest) = *(pDataStr + src + intAddr);
                    }
                    break;
                case 7:
                    src = addr & 0X7FFF;
                    intAddr = (addr >> 15) & 0X7FFF;
                    dest = (addr >> 30) & 0X7FFF;
                    flag = addr >> 45;
                    if(flag){
                        *(pDataNum + dest + intAddr) = *(pDataNum + src);
                    }else{
                        *(pDataStr + dest + intAddr) = *(pDataStr + src);
                    }  
                    break;
                // OJO!!! 8,9,10,11 requieren posiblemente pipes
                case 8:                
                    memref = addr;
                    // int leerInt;
                    // cin >> leerInt;                
                    // *(pDataNum + memref) = leerInt//leer desde control
                    break;
                case 9:
                    memref = addr;

                    // int printInt = *(pDataNum + memref);
                    // cout <<  printInt;
                    cout << "memref:"<<hex<<memref<<endl;
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
                    PC = *(pLitNum + intAddr); // PC es el pc
                    break;
                case 13:                                                            
                    intAddr = addr & 0x7FFF;
                    oper2Addr = (addr>>15) & 0x7FFF;
                    oper1Addr = (addr>>30) & 0x7FFF;
                    addr >>= 45;
                    flag= addr & 1;
                    op = addr >> 1;

                    if(flag){
                        switch(op){
                            //oper1 = *(pDataNum+oper1Addr);
                            //oper2 = *(pDataNum+oper2Addr);                         
                            case 0:
                                if(*(pDataNum+oper1Addr) >= *(pDataNum+oper2Addr)) PC = *(pDataNum+intAddr); //movemos el pc       
                                break;
                            case 1:
                                if(*(pDataNum+oper1Addr) > *(pDataNum+oper2Addr)) PC = *(pDataNum+intAddr); //movemos el pc       
                                break;
                            case 3: 
                                if(*(pDataNum+oper1Addr) <= *(pDataNum+oper2Addr)) PC = *(pDataNum+intAddr); //movemos el pc       
                                break;
                            case 4:
                                if(*(pDataNum+oper1Addr) < *(pDataNum+oper2Addr)) PC = *(pDataNum+intAddr); //movemos el pc       
                                break;
                            case 5:
                                if(*(pDataNum+oper1Addr) == *(pDataNum+oper2Addr)) PC = *(pDataNum+intAddr); //movemos el pc       
                                break;
                            case 6:
                                if(*(pDataNum+oper1Addr) != *(pDataNum+oper2Addr)) PC = *(pDataNum+intAddr); //movemos el pc       
                        }
                    }else{
                        switch(op){
                            //oper1 = *(pDataStr+oper1Addr);
                            //oper2 = *(pDataStr+oper2Addr);                         
                            case 0:
                                if(*(pDataStr+oper1Addr) >= *(pDataStr+oper2Addr)) PC = *(pDataStr+intAddr); //movemos el pc       
                                break;
                            case 1:
                                if(*(pDataStr+oper1Addr) > *(pDataStr+oper2Addr)) PC = *(pDataStr+intAddr); //movemos el pc       
                                break;
                            case 3: 
                                if(*(pDataStr+oper1Addr) <= *(pDataStr+oper2Addr)) PC = *(pDataStr+intAddr); //movemos el pc       
                                break;
                            case 4:
                                if(*(pDataStr+oper1Addr) < *(pDataStr+oper2Addr)) PC = *(pDataStr+intAddr); //movemos el pc       
                                break;
                            case 5:
                                if(*(pDataStr+oper1Addr) == *(pDataStr+oper2Addr)) PC = *(pDataStr+intAddr); //movemos el pc       
                                break;
                            case 6:
                                if(*(pDataStr+oper1Addr) != *(pDataStr+oper2Addr)) PC = *(pDataStr+intAddr); //movemos el pc       
                        }                        
                    }
                case 14:
                    cout << "op:"<<code<< endl;
                    cout << "terminado,"<<endl;
                    return 0; // OJO!!! terminar ejecucion del interpretador (Objeto creado)
                    
                    break;
                case 15:
                    cout << "op:"<<code<< endl;
                    // OJO!!! suspender proceso del interpretador, avisarle al control, hasta una reactivación
                    cout << "suspendido"<<endl;
                    return 0;
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
