//InterEwe.cpp
#include "InterEwe.h"

InterEwe::InterEwe()
{
	//cout << "InterEwe Object is being created" << endl;
}
InterEwe::~InterEwe(void)
{
	//cout << "InterEwe Object is being deleted" << endl;
}

int InterEwe::assignSections()
{
}

int InterEwe::readBew(char *shmname, char *file)
{
	fstream myReadFileBew(file, ios_base::binary | ios_base::in);
	int cont = 0, code; //borrar
	unsigned long long addr;
	unsigned char input, opcode, op;
	unsigned short memref, intAddr, strAddr, src, dest, oper1Addr, oper2Addr, mrSize;
	bool flag; // 1 = palabra(32 bits), 0 = char (8 bits)
	//borrar cuando no se use
	vector<unsigned long long> instructions;
	vector<unsigned char> opcodes;
	assignMemory(shmname);
	pMemg = (unsigned int *)pMem;
	pLitNum = (int *)(pMem + getBase(*(pMemg + 1)));
	pLitStr = (char *)(pMem + getBase(*(pMemg + 2))); //Char
	pDataNum = (int *)(pMem + getBase(*(pMemg + 3)));
	pDataStr = (char *)(pMem + getBase(*(pMemg + 4))); //Char
	pWorkLoad = (sem_t *)((int *)(pMem + getBase(*(pMemg + 5))));
	//sem_wait(&(*(pWorkLoad+0))); //Semamphore Call Example

	int readInt = 0, segSize, base;
	char *readStr, *writeStr, braek;
	unsigned int politica;
	// //cout << "Starting »» " << getpid() << " : " << ww << endl;
	// sem_wait(&(*(pWorkLoad+0))); // Block Resource
	// cout << "Before Write --> " << getpid() << endl;
	// cin >> ww;
	// cout << "After Write -->" << getpid() << " : " << ww << endl;
	// sem_post(&(*(pWorkLoad+0))); // Unblock Resource

	// if(ww == 100){
	//   string t = "";
	//   cout << "Process Blocked Press: continue -->" << getpid() << endl;;
	//   sem_wait(&(*(pWorkLoad+1))); // Block Resource
	//   cin >> t;
	//   cout << "Process Unlocked " << getpid() << " > " << ww << endl;
	//   sem_post(&(*(pWorkLoad+1))); // Unblock Resource
	// }

	if (myReadFileBew.is_open())
	{

		while (myReadFileBew.read((char *)&input, sizeof(unsigned char)))
		{
			cont++;
			// //cout <<"instrucción: "<<cont<<endl;
			opcode = input >> 4;
			addr = input & 0xF;
			code = opcode;
			switch (opcode){
			case 0:
				// //cout << "op: " << code << endl;
				for (int i = 0; i < 7; ++i)
				{
					myReadFileBew.read((char *)&input, sizeof(unsigned char));
					addr <<= 8;
					addr |= input;
				}
				addr >>= 30; //borra pad
				break;
			case 1:
				// //cout << "op: " << code << endl;
				for (int i = 0; i < 7; ++i)
				{
					myReadFileBew.read((char *)&input, sizeof(unsigned char));
					addr <<= 8;
					addr |= input;
				}
				addr >>= 30; //borra pad
				break;
			case 2:
				// //cout << "op: " << code << endl;
				for (int i = 0; i < 7; ++i)
				{
					myReadFileBew.read((char *)&input, sizeof(unsigned char));
					addr <<= 8;
					addr |= input;
				}
				addr >>= 30; //borra pad
				break;
			case 3:
				// //cout << "op: " << code << endl;
				for (int i = 0; i < 3; ++i)
				{
					myReadFileBew.read((char *)&input, sizeof(unsigned char));
					addr <<= 8;
					addr |= input;
				}
				memref = addr >> 13; //borra pad
				break;
			case 4:
				// //cout << "op: " << code << endl;
				for (int i = 0; i < 7; ++i)
				{
					myReadFileBew.read((char *)&input, sizeof(unsigned char));
					addr <<= 8;
					addr |= input;
				}
				addr >>= 29; //borra pad
				break;
			case 5:
				// //cout << "op: " << code << endl;
				for (int i = 0; i < 7; ++i)
				{
					myReadFileBew.read((char *)&input, sizeof(unsigned char));
					addr <<= 8;
					addr |= input;
				}
				addr >>= 11; //borra pad
				break;
			case 6:
				// //cout << "op: " << code << endl;
				for (int i = 0; i < 7; ++i)
				{
					myReadFileBew.read((char *)&input, sizeof(unsigned char));
					addr <<= 8;
					addr |= input;
				}
				addr >>= 14;
				break;
			case 7:
				// //cout << "op: " << code << endl;
				for (int i = 0; i < 7; ++i)
				{
					myReadFileBew.read((char *)&input, sizeof(unsigned char));
					addr <<= 8;
					addr |= input;
				}
				addr >>= 14;
				break;
			case 8:
				// //cout << "op: " << code << endl;
				for (int i = 0; i < 3; ++i)
				{
					myReadFileBew.read((char *)&input, sizeof(unsigned char));
					addr <<= 8;
					addr |= input;
				}
				addr >>= 13;
				break;
			case 9:
				// //cout << "op: " << code << endl;
				for (int i = 0; i < 3; ++i)
				{
					myReadFileBew.read((char *)&input, sizeof(unsigned char));
					addr <<= 8;
					addr |= input;
				}
				addr >>= 13;
				break;
			case 10:
				// //cout << "op: " << code << endl;
				for (int i = 0; i < 7; ++i)
				{
					myReadFileBew.read((char *)&input, sizeof(unsigned char));
					addr <<= 8;
					addr |= input;
				}
				addr >>= 30; //borra pad
				break;
			case 11:
				// //cout << "op: " << code << endl;
				for (int i = 0; i < 3; ++i)
				{
					myReadFileBew.read((char *)&input, sizeof(unsigned char));
					addr <<= 8;
					addr |= input;
				}
				addr >>= 13;
				break;
			case 12:
				// //cout << "op: " << code << endl;
				for (int i = 0; i < 3; ++i)
				{
					myReadFileBew.read((char *)&input, sizeof(unsigned char));
					addr <<= 8;
					addr |= input;
				}
				addr >>= 13;
				break;
			case 13:
				// //cout << "op: " << code << endl;
				for (int i = 0; i < 7; ++i)
				{
					myReadFileBew.read((char *)&input, sizeof(unsigned char));
					addr <<= 8;
					addr |= input;
				}
				addr >>= 11; //borra pad
				break;
				// los 13 y 14 no harían nada aca
			default:
				break;
			}
			// //cout << "address:" <<hex << addr << endl;
			instructions.push_back(addr); //addr sin opcode
			opcodes.push_back(opcode);
		}

		// este mapa me dice que politica tiene de 0 a 3
		map<unsigned int, int> mapDataNum;
		map<unsigned int, int> mapDataStr;

		for (int i = 6; i < 10; ++i)
		{
			base = ((*(pMemg + i)) >> 16);
			segSize = getSize(*(pMemg + i)) - base; // ej: 000B - 000A
			politica = *(pMemg + base);
			cout << segSize << endl;
			for (int j = 0; j < segSize; ++j)
			{

				segSize = politica & 0x0000FFFF; // sacamos los 4 bits de la derecha
				politica >>= 16;				 //sacamos los 4 bits de la izquierda (correrlo 16 bits)

				if (politica >> 15 == 1)
				{
					//datanum
					politica &= 0x1000;
					segSize &= 0x1000;
					for (int k = politica; k <= segSize; ++k)
					{
						mapDataNum[k] = i % 6; //se guarda la posicion sin salto
											   // cout <<"datanum =>"<<(int)mapDataNum[k] << endl;
					}
				}
				else
				{
					//datastring
					for (int k = input; k <= segSize; ++k)
					{
						// cout << "k: "<<k<<endl;
						mapDataStr[k] = i % 6; //se guarda la posicion en datanum
											   // cout <<"datastr =>"<<(int)mapDataStr[k] << endl;
					}
				}
			}
		}
		//cout << endl << "Interpretando: "<< endl;

		//   cout <<  endl << "Instrucciones: "<<endl;
		// for(int i = 0; i<instructions.size();++i){
		//     code = opcodes[i];
		//     cout << "opcode "<<hex << code << " ";
		//     cout << "address "<<hex << instructions[i]<< endl;
		// }
		int data;
		char* datastr;
		char aux;
		for (int PC = 0; PC < instructions.size(); ++PC)
		{
			opcode = opcodes[PC];
			addr = instructions[PC];
			code = opcode;
			// cout << endl << "PC "<<PC<<endl;
			// cout <<"op:"<<code<< endl;
			// cout << "address:" <<hex << addr << endl;
			switch (opcode)
			{
			case 0:
				intAddr = addr & 0x7FFF;
				memref = addr >> 15;
				//cout << "memref:"<<hex<<memref<<endl;
				//cout << "intAddr:"<<hex<<intAddr<<endl;
								
				data = readLitNum(intAddr);
				writeDatanum(memref,data,mapDataNum[memref]);			
				break;
			case 1:
				strAddr = addr & 0x7FFF;
				memref = addr >> 15;
				//cout << "memref:"<<hex<<memref<<endl;
				//cout << "strAddr:"<<hex<<strAddr<<endl;
				cont = 0;
				aux = readLitstr(strAddr+cont);
				while (aux != '0')
				{
					writeDatastr(memref+cont,aux,mapDataStr[memref+cont]);
					cont++;
					aux = readLitstr(strAddr+cont);										
				}
				writeDatastr(memref+cont,aux,mapDataStr[memref+cont]);
				break;
			case 2:
				intAddr = addr & 0x7FFF;
				memref = addr >> 15;
				//cout << "memref:"<<hex<<memref<<endl;
				//cout << "intAddr:"<<hex<<intAddr<<endl;			
				data = PC + readLitNum(intAddr); //movemos el pc
				writeDatanum(memref,data,mapDataNum[memref]);	
				break;
			case 3:
				memref = addr >> 13;
				// PC = *(pDataNum + memref);
				PC = readDatanum(memref,mapDataNum[memref]);

				//cout << "memref:"<<hex<<memref<<endl;
				//cout << "PC:"<<hex<<PC<<endl;
				break;
			case 4:
				src = addr & 0x7FFF;
				dest = (addr >> 15) & 0x7FFF;
				flag = addr >> 30;
				//cout << "src:"<< hex << src << endl;
				//cout << "dest:" << hex << dest << endl;
				//cout << "flag:" << hex << flag <<endl;
				if (flag)
				{					
					data = readLitNum(src);					
					writeDatanum(dest,data,mapDataNum[dest]);	
				}
				else
				{	
					cont = 0;
					aux = readDatastr(src+cont,mapDataStr[src+cont]);
					while (aux != '0')
					{
						writeDatastr(dest+cont,aux,mapDataStr[src+cont]);
						cont++;
						aux = readDatastr(src+cont,mapDataStr[src+cont]);
					}
					writeDatastr(dest+cont,aux,mapDataStr[src+cont]);
				}
				break;
			case 5:
				oper2Addr = addr & 0x7FFF;
				oper1Addr = (addr >> 15) & 0x7FFF;
				dest = (addr >> 30) & 0x7FFF;
				addr >>= 45;
				flag = addr & 1;
				op = addr >> 1;
				//cout << "oper2Addr:" << hex << oper2Addr <<endl;
				//cout << "oper1Addr:" << hex << oper1Addr <<endl;
				//cout << "dest:" << hex << dest <<endl;
				//cout << "flag:" << hex << flag <<endl;
				//cout << "op:" << hex << op <<endl;
				if (flag)
				{
					// en caso de que el bit este en 1, las operaciones se hacen en flag
					// oper1 = *(pDataNum + oper1Addr);
					// oper2 = *(pDataNum + oper2Addr);
					switch (op)
					{
					case 0:
						// result = oper1 + oper2;						
						data = *(pDataNum + oper1Addr) + *(pDataNum + oper2Addr);
						
						break;
					case 1:
						// result = oper1 - oper2;
						data = *(pDataNum + oper1Addr) - *(pDataNum + oper2Addr);
						break;
					case 2:
						// result = oper1 * oper2;
						data = *(pDataNum + oper1Addr) * *(pDataNum + oper2Addr);
						break;
					case 3:
						// result = oper1 / oper2;
						data = *(pDataNum + oper1Addr) / *(pDataNum + oper2Addr);
						break;
					case 4:
						// result = oper1 % oper2;
						data = *(pDataNum + oper1Addr) % *(pDataNum + oper2Addr);
						break;
					default:
						cerr << "Error: operador no existe " << endl;
						return 1;
					}
					writeDatanum(dest,data,mapDataNum[dest]);	
				}
				else
				{
					// operaciones a nivel de un caracter
					// oper1 = *(pDataStr + oper1Addr);
					// oper2 = *(pDataStr + oper2Addr);
					switch (op)
					{
					case 0:
						// result = oper1 + oper2;
						// *(pDataStr + dest) = *(pDataStr + oper1Addr) + *(pDataStr + oper2Addr);
						aux = readDatastr(oper1Addr,mapDataStr[oper1Addr]) + readDatastr(oper2Addr,mapDataStr[oper2Addr]);
					case 1:
						// result = oper1 - oper2;
						// *(pDataStr + dest) = *(pDataStr + oper1Addr) - *(pDataStr + oper2Addr);
						aux = readDatastr(oper1Addr,mapDataStr[oper1Addr]) - readDatastr(oper2Addr,mapDataStr[oper2Addr]);
					case 2:
						// result = oper1 * oper2 ;
						// *(pDataStr + dest) = *(pDataStr + oper1Addr) * *(pDataStr + oper2Addr);
						aux = readDatastr(oper1Addr,mapDataStr[oper1Addr]) * readDatastr(oper2Addr,mapDataStr[oper2Addr]);
					case 3:
						// result = oper1 / oper2;
						// *(pDataStr + dest) = *(pDataStr + oper1Addr) / *(pDataStr + oper2Addr);
						aux = readDatastr(oper1Addr,mapDataStr[oper1Addr]) / readDatastr(oper2Addr,mapDataStr[oper2Addr]);
					case 4:
						// result = oper1 % oper2;
						// *(pDataStr + dest) = *(pDataStr + oper1Addr) % *(pDataStr + oper2Addr);
						aux = readDatastr(oper1Addr,mapDataStr[oper1Addr]) % readDatastr(oper2Addr,mapDataStr[oper2Addr]);
					}
					 writeDatastr(dest,aux,mapDataStr[dest]); //*(pDataStr + dest)
				}
				break;
			case 6:
				intAddr = addr & 0X7FFF;
				src = (addr >> 15) & 0X7FFF;
				dest = (addr >> 30) & 0X7FFF;
				flag = addr >> 45;
				if (flag)
				{
					data = *(pDataNum + src + intAddr);
					writeDatanum(dest,data,mapDataNum[dest]);	
				}
				else
				{
					*(pDataStr + dest) = *(pDataStr + src + intAddr);
					aux = readDatastr(src+intAddr, mapDataStr[src+intAddr]);
					writeDatastr(dest,aux,mapDataStr[dest]);
				}
				break;
			case 7:
				src = addr & 0X7FFF;
				intAddr = (addr >> 15) & 0X7FFF;
				dest = (addr >> 30) & 0X7FFF;
				flag = addr >> 45;
				dest+=intAddr;
				if (flag)
				{
					data = *(pDataNum + src);
					
					writeDatanum(dest,data,mapDataNum[dest]);	
				}
				else
				{
					*(pDataStr) = *(pDataStr + src);
					aux = readDatastr(src, mapDataStr[src]);
					writeDatastr(src,aux,mapDataStr[src]);
				}
				break;
				// OJO!!! 8,9,10,11 requieren posiblemente pipes
			case 8: // Read Int
				memref = addr;
				sem_wait(&(*(pWorkLoad + 8))); // Block Resource
				cout << "Read Int: ";
				cin >> readInt;	
				writeDatanum(memref,readInt,mapDataNum[memref]);	
				sem_post(&(*(pWorkLoad + 8)));  // Unblock Resource
				// int leerInt;
				// cin >> leerInt;
				//*(pDataNum + memref) = leerInt//leer desde control
				break;
			case 9: // Write Int
				memref = addr;
				sem_wait(&(*(pWorkLoad + 8))); // Block Resource
				cout << "Write Int: " << readDatanum(memref,mapDataNum[memref]) << endl;
				sem_post(&(*(pWorkLoad + 8))); // Unblock Resource
				// int printInt = *(pDataNum + memref);
				// //cout <<  printInt;
				//cout << "memref:"<<hex<<memref<<endl;
				break;
			case 10: // Read Str
				mrSize = addr & 0x7FFF;
				dest = addr >> 15;

				cout << "dest:" << hex << dest << endl;
				cout << "mrSize:" << hex << mrSize <<endl;
				
				sem_wait(&(*(pWorkLoad + 8))); // Block Resource
				cout << "Read Str: ";
				cin >> readStr;                                           			
				sem_post(&(*(pWorkLoad + 8))); // Unblock Resource
				cont = 0;

				while (cont < mrSize && readStr[cont] != '0')
				{
					
					writeDatastr(dest+cont,readStr[cont],mapDataStr[dest+cont]);
					cont++;					
				}
				if (cont == mrSize)
					writeDatastr(dest+cont,'0',mapDataStr[dest+cont]);					

				break;
			case 11: // Write Str
				memref = addr;
				cont = 0;
				writeStr = "";
				aux = readDatastr(memref+cont,mapDataStr[memref+cont]);
				while (aux != '0')
				{
					writeStr += readDatastr(memref+cont,mapDataStr[memref+cont]);					
					cont++;
				}
				sem_wait(&(*(pWorkLoad + 8))); // Block Resource
				cout << "Write Str: "<< writeStr << endl; 
				sem_post(&(*(pWorkLoad + 8))); // Unblock Resource
				break;
			case 12:
				intAddr = addr;
				PC = readLitNum(intAddr);
				// *(pLitNum + intAddr); // PC es el pc
				break;
			case 13: // Write Str
				intAddr = addr & 0x7FFF;
				oper2Addr = (addr >> 15) & 0x7FFF;
				oper1Addr = (addr >> 30) & 0x7FFF;
				addr >>= 45;
				flag = addr & 1;
				op = addr >> 1;
				if (flag)
				{ // Para DataNum o DataString
					switch (op)
					{
						//oper1 = *(pDataNum+oper1Addr);
						//oper2 = *(pDataNum+oper2Addr);
					case 0:
						if (*(pDataNum + oper1Addr) >= *(pDataNum + oper2Addr))
							PC = readLitNum(intAddr); //movemos el pc
						break;
					case 1:
						if (*(pDataNum + oper1Addr) > *(pDataNum + oper2Addr))
							PC = readLitNum(intAddr); //movemos el pc
						break;
					case 3:
						if (*(pDataNum + oper1Addr) <= *(pDataNum + oper2Addr))
							PC = readLitNum(intAddr); //movemos el pc
						break;
					case 4:
						if (*(pDataNum + oper1Addr) < *(pDataNum + oper2Addr))
							PC = readLitNum(intAddr); //movemos el pc
						break;
					case 5:
						if (*(pDataNum + oper1Addr) == *(pDataNum + oper2Addr))
							PC = readLitNum(intAddr); //movemos el pc
						break;
					case 6:
						if (*(pDataNum + oper1Addr) != *(pDataNum + oper2Addr))
							PC = readLitNum(intAddr); //movemos el pc
					}
				}
				else
				{
					switch (op)
					{
						//oper1 = *(pDataStr+oper1Addr);
						//oper2 = *(pDataStr+oper2Addr);
					case 0:
						if (*(pDataStr + oper1Addr) >= *(pDataStr + oper2Addr))
							PC = readLitNum(intAddr); //movemos el pc
						break;
					case 1:
						if (*(pDataStr + oper1Addr) > *(pDataStr + oper2Addr))
							PC = readLitNum(intAddr); //movemos el pc
						break;
					case 3:
						if (*(pDataStr + oper1Addr) <= *(pDataStr + oper2Addr))
							PC = readLitNum(intAddr); //movemos el pc
						break;
					case 4:
						if (*(pDataStr + oper1Addr) < *(pDataStr + oper2Addr))
							PC = readLitNum(intAddr); //movemos el pc
						break;
					case 5:
						if (*(pDataStr + oper1Addr) == *(pDataStr + oper2Addr))
							PC = readLitNum(intAddr); //movemos el pc
						break;
					case 6:
						if (*(pDataStr + oper1Addr) != *(pDataStr + oper2Addr))
							PC = readLitNum(intAddr); //movemos el pc
					}
				}
			case 14:
				//Just return
				//cout << "op: " << code << endl;
				//cout << "terminado,"<<endl;
				return 0; // OJO!!! terminar ejecucion del interpretador (Objeto creado)
				break;
			case 15:
				/*
		Si sucede esta instrucción enviar información a Control y bloquear proceso, luego esperar información para activar
		Seeing Pipe and Block Process On C++
	*/
				sem_wait(&(*(pWorkLoad + 8))); // Block Resource
				cout << "Break, Enter Any Key: ";
				cin >> braek;
				sem_post(&(*(pWorkLoad + 8))); // Unblock Resource
				//cout << "op: " << code << endl;
				// OJO!!! suspender proceso del interpretador, avisarle al control, hasta una reactivación
				//cout << "suspendido"<<endl;
				return 0;
				break;
			default:
				cerr << "Error: opcode no válido" << endl;
				break;
			}
		}
	}
	myReadFileBew.close();
	return 0;
}


int InterEwe::assignMemory(char *shmname)
{
	int shm = shm_open(shmname, O_RDWR, 0600);
	size_mem = 1000;
	pMem = static_cast<char *>(mmap(NULL, size_mem, PROT_READ | PROT_WRITE, MAP_SHARED, shm, 0));
	if ((void *)pMem == (void *)-1)
	{
		cerr << "Problems with memory map en InterEwe" << endl;
		return 1;
	}
	//cout << "Shared memory already assigned"  << endl;
	return 0;
}

int InterEwe::getBase(int addr)
{
	return ((addr >> 16) << 2);
}

int InterEwe::getSize(int addr)
{
	return (addr & 0xFFFF);
}


int InterEwe::readLitNum(int pos){
  return *(pLitNum+pos);
}



char InterEwe::readLitstr(int pos){  
    return *(pLitStr+pos);
}


void InterEwe::writeDatastr(int pos, char data,int politica){

  if(politica==1){
    // prioridad lectores
    sem_wait(&(*pWorkLoad));
    *(pDataStr + pos) = data;
    sem_post(&(*pWorkLoad));
  }else if(politica==2){//prioridad escritores
    sem_wait (&(*(pWorkLoad+2)));
    //cout<<"Entre a la politica 2 writeDatastr "<<endl;
    cuentaescr++;
    if (cuentaescr == 1){
      sem_wait(&(*(pWorkLoad+3)) );
      sem_post (&(*(pWorkLoad+2)));
      sem_wait (&(*(pWorkLoad+4)));
    	*(pDataStr + pos) = data;
        
      sem_post (&(*(pWorkLoad+4)) );
      sem_wait (&(*(pWorkLoad+2)));
      cuentaescr--;
    }
    if (cuentaescr == 0){
      sem_post (&(*(pWorkLoad+3)));
      sem_post(&(*(pWorkLoad+2)));
    }
  }else if(politica==3){//Bloqueo
    sem_wait(&(*(pWorkLoad+7)));
    bloqueo--;
    //cout<<"Entre a la politica 3 writeDatastr------bloque: "<<bloqueo<<endl;
    
    *(pDataStr + pos) = data;
    bloqueo++;
    //cout<<"bloque: "<<bloqueo<<endl;
    sem_post(&(*(pWorkLoad+7)));

  }  else if (politica==4){
    //cout<<"Entre a la politica 4 writeDatastr"<<endl;
    
    *(pDataStr + pos) = data;
    
  }else{
      *(pDataStr + pos) = data;
  }


}





// OJO CON LOS CONTADORES
void InterEwe::writeDatanum(int pos, int data, int politica)
{
	if (politica == 1)
	{
		// prioridad lectores
		sem_wait(&(*pWorkLoad));
		//cout<<"Entre a la politica 1 writeDatanum"<<endl;
		*(pDataNum + pos) = data;		
	
		//sleep(1000);
		sem_post(&(*pWorkLoad));
	}
	else if (politica == 2)
	{ //prioridad escritores
		sem_wait(&(*(pWorkLoad + 2)));
		//cout<<"Entre a la politica 2 writeDatanum"<<endl;
		// OJO!!!
		cuentaescr++;
		if (cuentaescr == 1)
		{
			sem_wait(&(*(pWorkLoad + 3)));
			sem_post(&(*(pWorkLoad + 2)));
			sem_wait(&(*(pWorkLoad + 4)));
			*(pDataNum + pos) = data;	
			sem_post(&(*(pWorkLoad + 4)));
			sem_wait(&(*(pWorkLoad + 2)));
			cuentaescr--;
		}

		if (cuentaescr == 0)
		{
			sem_post(&(*(pWorkLoad + 3)));
			sem_post(&(*(pWorkLoad + 2)));
		}
	}
	else if (politica == 3)
	{ //Bloqueo
		sem_wait(&(*(pWorkLoad + 7)));
		bloqueo--;
		//cout<<"Entre a la politica 3 writeDatanum------bloque: "<<bloqueo<<endl;
		*(pDataNum + pos) = data;	
		bloqueo++;
		//cout<<"Bloqueo: "<<bloqueo<<endl;
		sem_post(&(*(pWorkLoad + 7)));
	}
	else if (politica == 4)
	{
		//cout<<"Entre a la politica 4 writeDatanum"<<endl;
		*(pDataNum + pos) = data;	
	}
}


int InterEwe::readDatanum(int pos,int politica){
  int valorRetornar;
  if (politica==1){//prioridad lectores

    //cout<<"Entre a la politica 1 de readDatanum"<<endl;
    sem_wait(&(*(pWorkLoad+1)));
    cuentalect++;
    if (cuentalect == 1){
      sem_wait(&(*(pWorkLoad)));
      sem_post(&(*(pWorkLoad+1)));
      valorRetornar= *(pDataNum+pos);
      sem_wait(&(*(pWorkLoad+1)));
      cuentalect--;
    }
    if (cuentalect == 0){
      sem_post(&(*(pWorkLoad)));
      sem_post(&(*(pWorkLoad+1)));
    }
  }else if(politica==2){//prioridad escritores

    //cout<<"Entre a la politica 2 de readDatanum"<<endl;
    sem_wait (&(*(pWorkLoad+5)));
    sem_wait (&(*(pWorkLoad+3)));
    sem_wait (&(*(pWorkLoad+6)));
    cuentalect2++;
    if (cuentalect2 == 1){
      sem_wait (&(*(pWorkLoad+4)));
      sem_post (&(*(pWorkLoad+6)));
      sem_post (&(*(pWorkLoad+3)));
      sem_post (&(*(pWorkLoad+5)));
      valorRetornar= *(pDataNum+pos);
      sem_wait (&(*(pWorkLoad+6)));
      cuentalect2 --;
    }
    if (cuentalect2 == 0){
      sem_post (&(*(pWorkLoad+4)));
      sem_post (&(*(pWorkLoad+6)));
    }

  }else if(politica==3){
    sem_wait(&(*(pWorkLoad+7)));
    bloqueo--;
    //cout<<"Entre a la politica 3 readDatanum------bloque: "<<bloqueo<<endl;

    valorRetornar= *(pDataNum+pos);
    bloqueo++;
    //cout<<"bloque: "<<bloqueo<<endl;

    sem_post(&(*(pWorkLoad+7)));
    return valorRetornar;
  }else if(politica==4){
    return *(pDataNum+pos);
  }
  return valorRetornar;
}


char InterEwe::readDatastr(int pos,int politica){
  char salida;

  if (politica==1){//prioridad lectores

    //cout<<"Entre a la politica 1 de readDatastr"<<endl;
    sem_wait(&(*(pWorkLoad+1)));
    cuentalect++;
    if (cuentalect == 1){
      sem_wait(&(*(pWorkLoad)));
      sem_post(&(*(pWorkLoad+1)));
    	salida = *(pDataStr+pos);
    
      sem_wait(&(*(pWorkLoad+1)));
      cuentalect--;
    }
    if (cuentalect == 0){
      sem_post(&(*(pWorkLoad)));
      sem_post(&(*(pWorkLoad+1)));
    }
  }else if(politica==2){//prioridad escritores

    //cout<<"Entre a la politica 2 de readDatastr"<<endl;
    sem_wait (&(*(pWorkLoad+5)));
    sem_wait (&(*(pWorkLoad+3)));
    sem_wait (&(*(pWorkLoad+6)));
    cuentalect2++;
    if (cuentalect2 == 1){
      sem_wait (&(*(pWorkLoad+4)));
      sem_post (&(*(pWorkLoad+6)));
      sem_post (&(*(pWorkLoad+3)));
      sem_post (&(*(pWorkLoad+5)));
     	salida = *(pDataStr+pos);

      sem_wait (&(*(pWorkLoad+6)));
      cuentalect2 --;
    }
    if (cuentalect2 == 0){
      sem_post (&(*(pWorkLoad+4)));
      sem_post (&(*(pWorkLoad+6)));
    }

  }else if(politica==3){
    sem_wait(&(*(pWorkLoad+7)));
    bloqueo--;
    //cout<<"Entre a la politica 3 readDatastr------bloque: "<<bloqueo<<endl;
   	salida = *(pDataStr+pos);
    bloqueo++;
    //cout<<"Bloqueo: "<<bloqueo<<endl;
    sem_post(&(*(pWorkLoad+7)));

  }else if(politica==4){

    //cout<<"Entre a la politica 4 readDatastr"<<endl;
    salida = *(pDataStr+pos);
  }
  return salida;
}
