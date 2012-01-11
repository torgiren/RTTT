#include "resfile.h"

using namespace std;

const char FILESTAMP[]="CRES";							// Typ pliku
const unsigned char VERSION=2;							// Wersja druga mojego cudownego resfile

Resfile res;

Resfile::Resfile():
	currFile(""), lastSize(0), resSize(0), version(0), bufor(NULL)
	{
	headerMap.clear();
	header.clear();

	/*if(sizeof(unsigned int)!=4 || sizeof(char)!=1)
		{
		printf("FAIL: Resfile.Resfile: Wielkosci zmiennych sa inne niz oczekiwano\n");
		throw exception();
		}*/
	}

Resfile::~Resfile()
	{
	if(inFile.is_open())
		inFile.close();
	headerMap.clear();
	header.clear();
	}

Resfile& Resfile::get()
	{
	return res;
	}

bool Resfile::open(const std::string& resName)
	{
	if(resName.compare(currFile)==0)	// Jesli juz otwarte - przerwij
		return 1;
	//printf("INFO: Resfile.open: Otwieranie pliku \"%s\"\n", resName);
	if(inFile.is_open())				// W przeciwnym razie zamknij plik, o ile jakis otwarty
		inFile.close();
	inFile.open(resName.c_str(), fstream::in|fstream::binary);
	if(inFile==NULL)
		return 0;
	if(!headerMap.empty())
		headerMap.clear();
	header.clear();
	currFile=resName;
/// Pobieranie wielkosci pliku
	inFile.seekg(0, ios::end);
	resSize=inFile.tellg();
	inFile.seekg(0, ios::beg);
/// Sprawdzanei wersji
	if(resSize<5)
		{
		printf("FAIL: Resfile.open: Brak naglowka \"%s\"\n", resName.c_str());
		return 0;
		}
	char ident[strlen(FILESTAMP)+1];
	inFile.read(ident, strlen(FILESTAMP)*sizeof(char));
	ident[strlen(FILESTAMP)]='\0';
	inFile.read(reinterpret_cast<char*>(&version), sizeof(char));
	if(strcmp(ident, FILESTAMP)!=0 || version!=VERSION)
		{
		printf("FAIL: Resfile.open: Nieobslugiwana wersja resfile \"%s\"\n", resName.c_str());
		inFile.close();
		return 0;
		}
/// Wczytywanie naglowka
	unsigned int headSize, count;
	inFile.read(reinterpret_cast<char*>(&headSize), sizeof(unsigned int));
	inFile.read(reinterpret_cast<char*>(&count), sizeof(unsigned int));
	//printf("INFO: Resfile.open: Ilosc plikow: %u\n", count);
	header.reserve(count);
	for(unsigned int i=0; i<count; i++)
		{
	/// Info o pliku
		unsigned int start, size, ucsize=0;
		unsigned char flags;
		inFile.read(reinterpret_cast<char*>(&start), sizeof(unsigned int));
		inFile.read(reinterpret_cast<char*>(&size), sizeof(unsigned int));			// Wielkosc danych
		inFile.read(reinterpret_cast<char*>(&flags), sizeof(unsigned char));
		if(flags&COMPRESSED)
			inFile.read(reinterpret_cast<char*>(&ucsize), sizeof(unsigned int));		// Wielkosc po rozpakowaniu
		try
			{
			header.push_back(HeadEntry(headSize+start, size, ucsize, flags));
			}
		catch(bad_alloc &)
			{
			printf("FAIL: Resfile.open: Nie udalo sie dodac info o pliku do tablicy \"%s\"\n", resName.c_str());
			continue;
			}
		//printf("INFO: Resfile.open: Start: %u, Size: %u, Packd: %d, Unpackd: %u\n",  start, size, flags&COMPRESSED, ucsize);
	/// Nazwa itp
		unsigned int nameLen;
		char *name;
		inFile.read(reinterpret_cast<char*>(&nameLen), sizeof(unsigned int));
		try
			{
			name=new char[nameLen+1];
			}
		catch(bad_alloc &)
			{
			printf("FAIL: Resfile.open: Nie udalo sie zajac miejsca na nazwe pliku \"%s\" (%u)\n", resName.c_str(), nameLen);
			continue;
			}
		inFile.read(name, nameLen);
		name[nameLen]='\0';
		//header[i].name=name;
		headerMap[name]=&header[i];
		//printf("\t\"%s\"\n", name);
		delete [] name;
		}
	return 1;
	}

char* Resfile::load(HeadEntry& entry)
	{
	try
		{
		bufor=new char[entry.size+1];
		}
	catch(bad_alloc &)
		{
		printf("FAIL: Resfile.load: Nie udalo sie zajac pamieci na plik (%u)\n", entry.size+1);
		return NULL;
		}
	//printf("> %u, %u, %u\n", entry.size, entry.ucsize, entry.flags);
	inFile.seekg(entry.start, ios::beg);
	inFile.read(bufor, entry.size);
	bufor[entry.size]='\0';
	lastSize=entry.size;
	if(entry.flags&COMPRESSED)
		{
		char *cbufor=bufor;
		try
			{
			bufor=new char[entry.ucsize+1];
			}
		catch(bad_alloc &)
			{
			printf("FAIL: Resfile.load: Nie udalo sie zajac pamieci na bufor (%u)\n", entry.ucsize+1);
			delete [] cbufor;
			return NULL;
			}
		int ret=uncompress((Bytef *)bufor, (uLongf *)(&entry.ucsize), (Bytef *)cbufor, entry.size);
		delete [] cbufor;
		if(ret!=Z_OK)
			{
			printf("FAIL: Resfile.load: Nie udalo sie rozpakowac pliku (%d)\n", ret);
			delete [] bufor;
			return NULL;
			}
		bufor[entry.ucsize]='\0';
		lastSize=entry.ucsize;
		}
	return bufor;
	}

char* Resfile::load(const std::string& resName, const std::string& fileName)
	{
	//printf("> Wczytywanie \"%s\", \"%s\"\n", resName, fileName);
	if(!open(resName))
		{
		printf("FAIL: Resfile.load: Nie udalo sie otworzyc pliku \"%s\"\n", resName.c_str());
		return NULL;
		}
	if(!checkFile(fileName))
		{
		printf("FAIL: Resfile.load: Nie znaleziono pliku \"%s\"\n", fileName.c_str());
		return NULL;
		}
	if(headerMap.find(fileName)!=headerMap.end() && headerMap[fileName]!=NULL)
		return load(*headerMap[fileName]);
	printf("FAIL: Reslile.load: Nie znaleziono \"%s\"\n", fileName.c_str());
	return NULL;
	}

char* Resfile::load(const std::string& resName, unsigned int num)
	{
	if(!open(resName))
		{
		printf("FAIL: Resfile.load: Nie udalo sie otworzyc pliku \"%s\"\n", resName.c_str());
		return NULL;
		}
	if(!checkFile(num))
		{
		printf("FAIL: Resfile.load: Nie znaleziono pliku %u\n", num);
		return NULL;
		}
	return load(header[num]);
	}

char* Resfile::load(const std::string& name)
	{
	if(name.length()<2)
		{
		printf("FAIL: Resfile.load: Zla nazwa pliku (\"%s\")\n", name.c_str());
		return NULL;
		}
	/*Parser pars(name, ":");
	if(pars.count()<2)
		{
		printf("FAIL: Resfile.load: Zla nazwa pliku (\"%s\")\n", name);
		return NULL;
		}
	return load(pars[0].c_str(), pars[1].c_str());*/
	return load(currFile, name);
	}

char* Resfile::loadRes(const std::string& resName)
	{
	if(!open(resName))
		{
		printf("FAIL: Resfile.load: Nie udalo sie otworzyc pliku \"%s\"\n", resName.c_str());
		return NULL;
		}
	inFile.seekg(0, ios::end);
	lastSize=inFile.tellg();
	inFile.seekg(0, ios::beg);
	try
		{
		bufor=new char[lastSize];
		}
	catch(bad_alloc &)
		{
		printf("FAIL: Resfile.load: Nie udalo sie zajac miejsca na bufor (%u)\n", lastSize);
		return NULL;
		}
	inFile.read(bufor, lastSize);
	//bufor[lastSize]='\0';
	return bufor;
	}


bool Resfile::checkFile(const std::string& fileName)
	{
	if(headerMap.find(fileName)==headerMap.end())
		return 0;
	return 1;
	}

bool Resfile::checkFile(unsigned int num)
	{
	//printf("INFO: Resfile.checkFile: %u/%u\n", num, header.size());
	if(num>=header.size())
		return 0;
	return 1;
	}


unsigned int Resfile::getSize(const std::string& fileName)
	{
	map<string, HeadEntry *>::iterator it=headerMap.find(fileName);
	if(it==headerMap.end())
		return 0;
	if((*it).second==NULL)
		return 0;
	return (*it).second->size;
	}

unsigned int Resfile::getSize(unsigned int num)
	{
	if(checkFile(num))
		return 0;
	return header[num].size;
	}


unsigned int Resfile::getFileCount(const std::string& resName)
	{
	unsigned int count=0;
	string lastFile=currFile;
	if(open(resName))
		count=header.size();
	//if(lastFile.length()>1 && !open(lastFile.c_str()))
	//	printf("FAIL: Resfile.load: Nie udalo sie otworzyc pliku \"%s\"\n", lastFile.c_str());
	return count;
	}

const string& Resfile::getFileName(unsigned int num)
	{
	static string none="";
	if(num>=header.size())
		return none;
	for(map<string, HeadEntry *>::iterator it=headerMap.begin(); it!=headerMap.end(); ++it)
		{
		if(it->second==&header[num])
			return it->first;
		}
	return none;
	}
