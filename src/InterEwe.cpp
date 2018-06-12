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

	int readInt = 0;
	char *readStr,*writeStr, braek;
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
			switch (opcode)
			{
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
	
		//cout << endl << "Interpretando: "<< endl;

		  cout <<  endl << "Instrucciones: "<<endl;
        for(int i = 0; i<instructions.size();++i){
            code = opcodes[i];
            cout << "opcode "<<hex << code << " ";
            cout << "address "<<hex << instructions[i]<< endl;
        }               
        



		for (int PC = 0; PC < instructions.size(); ++PC)
		{
			opcode = opcodes[PC];
			addr = instructions[PC];
			code = opcode;
			cout << endl << "PC "<<PC<<endl;
			cout <<"op:"<<code<< endl;
			cout << "address:" <<hex << addr << endl;
			switch (opcode)
			{
			case 0:
				intAddr = addr & 0x7FFF;
				memref = addr >> 15;
				//cout << "memref:"<<hex<<memref<<endl;
				//cout << "intAddr:"<<hex<<intAddr<<endl;
				*(pDataNum + memref) = *(pLitNum + intAddr);
				break;
			case 1:
				strAddr = addr & 0x7FFF;
				memref = addr >> 15;
				//cout << "memref:"<<hex<<memref<<endl;
				//cout << "strAddr:"<<hex<<strAddr<<endl;
				cont = 0;
				// aux = *(pLitStr + strAddr + cont)
				while (*(pLitStr + strAddr + cont) != '0')
				{
					*(pDataStr + memref + cont) = *(pLitStr + strAddr + cont);
					cont++;
				}
				*(pDataStr + memref + cont) = *(pLitStr + strAddr + cont);
				break;
			case 2:
				intAddr = addr & 0x7FFF;
				memref = addr >> 15;
				//cout << "memref:"<<hex<<memref<<endl;
				//cout << "intAddr:"<<hex<<intAddr<<endl;
				*(pDataNum + memref) = PC + *(pLitNum + intAddr);
				break;
			case 3:
				memref = addr >> 13;
				PC = *(pDataNum + memref);
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
					*(pDataNum + dest) = *(pDataNum + src);
				}
				else
				{
					cont = 0;
					// aux = *(pDataStr + src + cont);
					while (*(pDataStr + src + cont) != '0')
					{
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
						cerr << "Error: operador no existe " << endl;
						return 1;
					}
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
				dest = (addr >> 30) & 0X7FFF;
				flag = addr >> 45;
				if (flag)
				{
					*(pDataNum + dest) = *(pDataNum + src + intAddr);
				}
				else
				{
					*(pDataStr + dest) = *(pDataStr + src + intAddr);
				}
				break;
			case 7:
				src = addr & 0X7FFF;
				intAddr = (addr >> 15) & 0X7FFF;
				dest = (addr >> 30) & 0X7FFF;
				flag = addr >> 45;
				if (flag)
				{
					*(pDataNum + dest + intAddr) = *(pDataNum + src);
				}
				else
				{
					*(pDataStr + dest + intAddr) = *(pDataStr + src);
				}
				break;
				// OJO!!! 8,9,10,11 requieren posiblemente pipes
			case 8: // Read Int				
				memref = addr;
				sem_wait(&(*(pWorkLoad + 8))); // Block Resource
				cout << "Read Int: ";
				cin >> readInt;
				readInt = 99;
				*(pDataNum + memref) = readInt; //leer desde control
				sem_post(&(*(pWorkLoad + 8)));  // Unblock Resource
				// int leerInt;
				// cin >> leerInt;
				//*(pDataNum + memref) = leerInt//leer desde control
				break;
			case 9: // Write Int				
				memref = addr;
				sem_wait(&(*(pWorkLoad + 8))); // Block Resource
				cout << "Write Int: " << *(pDataNum + memref) << endl;
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

				while(cont<mrSize && readStr[cont] != '0'){
					*(pDataStr+dest+cont) = readStr[cont];
					cont++;
				}
				if(cont == mrSize) 
					*(pDataStr+dest+cont) = '0';
				
				break;
			case 11: // Write Str
				memref = addr;
				cont = 0;
				writeStr = "";
				while(*(pDataStr + memref + cont) != '0')
				{
					writeStr += *(pDataStr + memref + cont);
					cont++;
				}
				sem_wait(&(*(pWorkLoad + 8))); // Block Resource
				cout << "Write Str: "<< writeStr << endl; 
				sem_post(&(*(pWorkLoad + 8))); // Unblock Resource
				break;
			case 12:
				intAddr = addr;
				PC = *(pLitNum + intAddr); // PC es el pc
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
							PC = *(pLitNum + intAddr); //movemos el pc
						break;
					case 1:
						if (*(pDataNum + oper1Addr) > *(pDataNum + oper2Addr))
							PC = *(pLitNum + intAddr); //movemos el pc
						break;
					case 3:
						if (*(pDataNum + oper1Addr) <= *(pDataNum + oper2Addr))
							PC = *(pLitNum + intAddr); //movemos el pc
						break;
					case 4:
						if (*(pDataNum + oper1Addr) < *(pDataNum + oper2Addr))
							PC = *(pLitNum + intAddr); //movemos el pc
						break;
					case 5:
						if (*(pDataNum + oper1Addr) == *(pDataNum + oper2Addr))
							PC = *(pLitNum + intAddr); //movemos el pc
						break;
					case 6:
						if (*(pDataNum + oper1Addr) != *(pDataNum + oper2Addr))
							PC = *(pLitNum + intAddr); //movemos el pc
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
							PC = *(pLitNum + intAddr); //movemos el pc
						break;
					case 1:
						if (*(pDataStr + oper1Addr) > *(pDataStr + oper2Addr))
							PC = *(pLitNum + intAddr); //movemos el pc
						break;
					case 3:
						if (*(pDataStr + oper1Addr) <= *(pDataStr + oper2Addr))
							PC = *(pLitNum + intAddr); //movemos el pc
						break;
					case 4:
						if (*(pDataStr + oper1Addr) < *(pDataStr + oper2Addr))
							PC = *(pLitNum + intAddr); //movemos el pc
						break;
					case 5:
						if (*(pDataStr + oper1Addr) == *(pDataStr + oper2Addr))
							PC = *(pLitNum + intAddr); //movemos el pc
						break;
					case 6:
						if (*(pDataStr + oper1Addr) != *(pDataStr + oper2Addr))
							PC = *(pLitNum + intAddr); //movemos el pc
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
