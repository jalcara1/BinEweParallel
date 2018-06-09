//InterEwe.cpp
#include "InterEwe.h"

InterEwe::InterEwe() {
  cout << "InterEwe Object is being created" << endl;
}
InterEwe::~InterEwe(void) {
  cout << "InterEwe Object is being deleting" << endl;
}
int InterEwe::readBew(char* shmname, char* file) {
  cout << shmname << " -:- " << file << endl;
  if(assignMemory(shmname)){
    cerr << "Error With Memory" << endl;
    return 1;
  }else{
    *(pMemg+0x3c) = 0xFF;
  }
  cout << "1" << endl;
  fstream myReadFileBew(file,ios_base::binary|ios_base::in);
  int cont =0, code;
  unsigned long long addr;
  unsigned char input, aux, opcode, op;
  unsigned short memref, intAddr, strAddr, src, dest, oper1, oper2, mrSize;
  bool dataNum; // 1 = palabra(32 bits), 0 = char (8 bits)
  cout << "2" << endl;
  if(myReadFileBew.is_open()){
    while(myReadFileBew.read((char*)&input,sizeof(unsigned char))){
      cont++;
      cout << "Instruction: " << cont << endl;
      opcode = input >> 4;
      addr = input & 0xF;
      code = opcode;
      cout << "3" << endl;
      switch (opcode) {
      case 0:
	cout << "op: " << code << endl;
	for(int i =0; i< 7; ++i){
	  myReadFileBew.read((char*)&aux,sizeof(unsigned char));
	  addr <<= 8;
	  addr |= aux;
	}
	cout << "address: " << hex << addr << endl;
	addr >>= 30; //Deleting pad
	intAddr = addr & 0x7FFF;
	memref =  addr >> 15;
	cout << "memref: " << hex << memref << endl;
	cout << "intAddr: " << hex << intAddr << endl;
	// hacer lo que debe hacer
	break;
      case 1:
	cout << "op: " << code << endl;
	for(int i =0; i< 7; ++i){
	  myReadFileBew.read((char*)&aux,sizeof(unsigned char));
	  addr <<= 8;
	  addr |= aux;
	}
	cout << "address: " << hex << addr << endl;
	addr >>= 30; //Deleting pad
	strAddr = addr & 0x7FFF;
	memref =  addr >> 15;
                    
	cout << "memref:"<<hex<<memref<<endl;
	cout << "strAddr:"<<hex<<strAddr<<endl;
	//hacer lo que se debe hacer
	break;
      case 2:
	cout << "op: " << code << endl;
	for(int i =0; i< 7; ++i){
	  myReadFileBew.read((char*)&aux,sizeof(unsigned char));
	  addr <<= 8;
	  addr |= aux;
	}                    
	cout << "address: " << hex << addr << endl;
	addr >>= 30; //borra pad
	intAddr = addr & 0x7FFF;
	memref =  addr >> 15;
	cout << "memref: "<< hex << memref << endl;
	cout << "intAddr: "<< hex << intAddr << endl;
	// hacer lo que debe hacer
	break;
      case 3:
	cout << "op: " << code << endl;
	for(int i =0; i< 3; ++i){
	  myReadFileBew.read((char*)&aux,sizeof(unsigned char));
	  addr <<= 8;
	  addr |= aux;
	}
	cout << "address: " << hex << addr << endl;
	memref = addr >> 13; //borra pad
	// hacer lo que debe hacer
	break;
      case 4:
	cout << "op: " << code << endl;
	for(int i =0; i< 7; ++i){
	  myReadFileBew.read((char*)&aux,sizeof(unsigned char));
	  addr <<= 8;
	  addr |= aux;
	}
	cout << "address: " << hex << addr << endl;
	addr >>= 29 ; //borra pad
	src = addr & 0x7FFF;
	dest = (addr >> 15) & 0x7FFF;
	dataNum = addr >> 30;
	if(dataNum){
	  //datanum
	}else{
	  //datastring
	}
	break;
      case 5:
	cout << "op: " << code << endl;
	for(int i =0; i< 7; ++i){
	  myReadFileBew.read((char*)&aux,sizeof(unsigned char));
	  addr <<= 8;
	  addr |= aux;
	}
	cout << "address: " << hex << addr << endl;
	addr >>= 11 ; //borra pad
	oper2 = addr & 0x7FFF;
	oper1 = (addr >> 15) & 0x7FFF;
	dest = (addr >> 30) & 0x7FFF;
	addr >>= 45;
	dataNum= addr & 1;
	op = addr >> 1;
	break;
      case 6:
	for(int i =0; i< 7; ++i){
	  myReadFileBew.read((char*)&aux,sizeof(unsigned char));
	  addr <<= 8;
	  addr |= aux;
	}
	cout << "address: " << hex << addr << endl;
	addr >>= 14;
	intAddr = addr & 0X7FFF;
	src = (addr >> 15) & 0X7FFF;
	dest = (addr>>30) & 0X7FFF;
	dataNum = addr >> 45;
	if(dataNum){
	  
	}else{
	  
	}
	break;
      case 7:
	cout << "op: " << code << endl;                          
	for(int i =0; i< 7; ++i){
	  myReadFileBew.read((char*)&aux,sizeof(unsigned char));
	  addr <<= 8;
	  addr |= aux;
	}
	cout << "address: " << hex << addr << endl;
	addr >>= 14;
	src= addr & 0X7FFF;
	intAddr = (addr >> 15) & 0X7FFF;
	dest = (addr >> 30) & 0X7FFF;
	dataNum = addr >> 45;
	if(dataNum){

	}else{
                        
	}  
	break;
      case 8:
	cout << "op: " << code << endl;
	for(int i =0; i< 3; ++i){
	  myReadFileBew.read((char*)&aux,sizeof(unsigned char));
	  addr <<= 8;
	  addr |= aux;
	}
	cout << "address: " << hex << addr << endl;
	memref = addr >> 13;
	break;
      case 9:
	cout << "op: " << code << endl;             
	for(int i =0; i< 3; ++i){
	  myReadFileBew.read((char*)&aux,sizeof(unsigned char));
	  addr <<= 8;
	  addr |= aux;
	}
	cout << "address: " << hex << addr << endl;
	memref = addr >> 13;
	break;
      case 10:
	cout << "op: " << code << endl;
	for(int i =0; i< 7; ++i){
	  myReadFileBew.read((char*)&aux,sizeof(unsigned char));
	  addr <<= 8;
	  addr |= aux;
	}
	cout << "address: " << hex << addr << endl;
	addr >>= 30; //borra pad
	mrSize = addr & 0x7FFF;
	dest =  addr >> 15;
	cout << "dest: " << hex << dest << endl;
	cout << "mrSize: " << hex << mrSize <<endl;
	// hacer lo que debe hacer
	break;
      case 11:
	cout << "op: " << code << endl;     
	for(int i =0; i< 3; ++i){
	  myReadFileBew.read((char*)&aux,sizeof(unsigned char));
	  addr <<= 8;
	  addr |= aux;
	}
	cout << "address: " << hex << addr << endl;
	memref = addr >> 13;
	break;
      case 12:
	cout << "op: " << code << endl;     
	for(int i =0; i< 3; ++i){
	  myReadFileBew.read((char*)&aux,sizeof(unsigned char));
	  addr <<= 8;
	  addr |= aux;
	}
	cout << "address: " << hex << addr << endl;
	intAddr = addr >> 13;
	break;
      case 13:
	cout << "op: " << code << endl;
	cout << "op: " << code << endl;
	for(int i =0; i< 7; ++i){
	  myReadFileBew.read((char*)&aux,sizeof(unsigned char));
	  addr <<= 8;
	  addr |= aux;
	}
	cout << "address: " << hex << addr << endl;
	addr >>= 11 ; //borra pad
	intAddr = addr & 0x7FFF;
	oper2 = (addr>>15) & 0x7FFF;
	oper1 = (addr>>30) & 0x7FFF;
	addr >>= 45;
	dataNum= addr & 1;
	op = addr >> 1;
      case 14:
	cout << "op: " << code << endl;
	break;
      case 15:
	cout << "op: " << code << endl;
	break;
      default:
	cerr << "Error: opcode no válido"<< endl;
	break;
      }
      cout << endl;
    }
  }
  myReadFileBew.close();
  return 0;
}
int InterEwe::assignMemory(char* shmname) {
  int shm = shm_open(shmname, O_RDWR , 0600);
  size_mem= 1000;
  pMem = static_cast<unsigned char*>(mmap(NULL, size_mem, PROT_READ | PROT_WRITE, MAP_SHARED, shm, 0));
    
  if ((void *) pMemg == (void *) -1) {
    cerr << "Problems with memory map" << endl;
    return 1;
  }
  cout << "Shared memory already assigned"  << endl;
  pMemg = (unsigned int *)pMem;
  return 0;
}
