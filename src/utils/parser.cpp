#include "parser.h"

/************************************************
* Parser(string str="")				// tworzy parser z tekstem 'str' i spacja jako delimiterem
* Parser& operator=(char* arg);		// przypisuje nowy tekst do parsera
* string operator[] (int arg);		// pokazuje 'arg' element
* operator const char*();			// zwraca tekst parsera
// * void destroy();					// niszczy parser. Nie wiem po co to, ale nvm
* void setText(string str);			// ustawia tekst na 'str'					to samo co =
* void setDelimiter(string str);	// ustawia delimiter na 'str'
* void parse();						// parsuje i znajduje wyrazy
* int count();						// zwraca ilosc wyrazow w parserze
* string show(int numer);			// zwraca 'numer' element					to samo co []
* void del(int numer);				// kasuje element 'numer'
* void ins(int numer, string str);	// wstawia element przed 'numer' ... przed czy po~?
* void swap(int numer, string str);	// zastepuje element 'numer' tekstem 'str'
* int find(string tekst);			// zwraca numer elementu 'tekst', o ile jest
* int val(int numer);				// zwraca element 'numer' jako liczbe
* bool isVal(int numer);			// sprawdza, czy element 'numer' jest liczba
*************************************************/

using namespace std;

Parser::Parser(string str, string delim)
	{
	text=str;
	delimiter=delim;
	parse();
	}
Parser& Parser::operator= (string arg)
	{
	setText(arg);
	return *this;
	}

Parser& Parser::operator= (const char *arg)
	{
	setText(arg);
	return *this;
	}

Parser::~Parser()
	{

	}
/*Parser& Parser::operator = (char* arg)
	{
	setText(arg);
	return *this;
	}*/
/*Parser& operator+=(string arg)
	{
	setText(text+arg);
	}*/
string Parser::operator[] (int arg)
	{
	return show(arg);
	}
Parser::operator const char*()
	{
	return text.c_str();
	}
/*void Parser::destroy()	// Gin, bezuzyteczna funkcjo, huhu!
	{
	delete this;
	}*/
/**************************** Ustawianie tekstu na nowy i szukanie wyrazow **************/
void Parser::setText(string str)
	{
	text=str;
	parse();
	}
// Ustawianie oddzielacza na nowy i liczenie elementow~
void Parser::setDelimiter(string str)
	{
	delimiter=str;
	parse();
	}
/**************************** Szukanie wyrazow ******************************************/
void Parser::parse()
	{
	elementy.clear();
	int poczatek=0;
	int dlugosc=0;
	bool delim=0;
	for(int i=0; i<(int)text.length()+1; i++)			// size?	// a, ok, alias na length	// trzymajmy sie jednego stylu, ok~?
		{
		//printf("Znak[%d]: % 4d\n", i, text[i]);
		delim=0;
		for(unsigned int j=0; j<delimiter.length(); j++)
			if(text[i]==delimiter[j] || text[i]=='\0')
				{
				delim=1;
				break;
				}
		if(delim==1 && dlugosc>0)
			{
			elementy.push_back(poczatek);
			elementy.push_back(dlugosc);
			//printf("OK  : Dodawanie - poczatek %d, dlugosc %d\n", poczatek, dlugosc);
			dlugosc=0;
			}
		else if(delim==0)
			{
			if(dlugosc==0)
				poczatek=i;
			dlugosc++;
			}
		/*if(text[i]!='\r' && text[i]!='\n')
			printf("INFO: %d - znak %c, delim %d, dlugosc %d\n", i, text[i], delim, dlugosc);
		else
			printf("INFO: %d - znak %d, delim %d, dlugosc %d\n", i, text[i], delim, dlugosc);*/
		}
	/*if(dlugosc!=0)
		{
		elementy.push_back(poczatek);
		elementy.push_back(dlugosc);
		}*/
	//printf("INFO: Parser.parse: Ilosc elementow: %d\n", elementy.size());
	}
/**************************** Sprawdzanie ilosci elementow ******************************/
int Parser::count()
	{
	return elementy.size()/2;
	}
/**************************** Wybieranie elementu o pewnym numerze **********************/
string Parser::show(int numer)
	{
	if(numer>=count())
		{
		printf("FAIL: Parser.show: Element %d nie istnieje\n", numer);
		return "";
		}
	return text.substr(elementy[numer*2], elementy[numer*2+1]);
	}
/**************************** Kasowanie wybranego elementu ******************************/
void Parser::del(int numer)
	{
	if(numer>=count())
		{
		printf("FAIL: Parser.del: Element %d nie istnieje\n", numer);
		return;
		}
	int poczatek=elementy[numer*2];
	//int dlugosc=elementy[numer*2+1];
	int dlugosc=(elementy.size()>(unsigned int)numer*2+2)?elementy[numer*2+2]-poczatek:elementy[numer*2+1];
	//printf("> Kasowanie start: %d, dlugosc: %d\n> str: %s\n", poczatek, dlugosc, text.c_str());
	/*for(int i=poczatek-1; i>=0; i--)					// Przycinanie poczatku
		{
		bool found=0;
		for(unsigned int j=0; j<delimiter.length(); j++)
			{
			if(text[i]!=delimiter[j])
				continue;
			poczatek--;
			found=1;
			}
		if(!found)
			break;
		}
	for(unsigned int i=poczatek+dlugosc+1; i<text.length(); i++)	// Przycinanie konca
		{
		bool found=0;
		for(unsigned int j=0; j<delimiter.length(); j++)
			{
			if(text[i]!=delimiter[j])
				continue;
			dlugosc++;
			found=1;
			}
		if(!found)
			break;
		}*/
	text.erase(poczatek, dlugosc);						// Po przycieciu zostaje jeden znak delimitera z konca
	parse();
	}
/**************************** Wstawianie tekstu po elemencie ****************************/
void Parser::ins(int numer, string str)
	{
	if(numer>=count())
		{
		printf("FAIL: Parser.ins: Element %d nie istnieje\n", numer);
		return;
		}
	text.insert(elementy[(numer+1)*2], str+delimiter[0]);
	parse();
	}
/**************************** Zamiana elementu na drugi *********************************/
void Parser::swap(int numer, string str)
	{
	if(numer>=count())
		{
		printf("FAIL: Parser.swap: Element %d nie istnieje\n", numer);
		return;
		}
	del(numer);
	parse();
	ins(numer-1, str);
	}
/**************************** Znajdywanie elementu **************************************/
int Parser::find(string text)
	{
	for(int i=0; i<count(); i++)
		{
		if(show(i)==text.c_str())
			return i;
		}
	return -1;
	}
/**************************** Wybieranie elementu o pewnym numerze **********************/
int Parser::val(int numer)
	{
	if(numer>=count())
		{
		printf("FAIL: Parser.val: Element %d nie istnieje\n", numer);
		return 0;
		}
	return atoi(show(numer).c_str());
	}

float Parser::valFloat(int numer)
	{
	if(numer>=count())
		{
		printf("FAIL: Parser.val: Element %d nie istnieje\n", numer);
		return 0;
		}
	return atof(show(numer).c_str());
	}

bool Parser::isVal(int numer)
	{
	if(numer>=count())
		{
		printf("FAIL: Parser.isVal: Element %d nie istnieje\n", numer);
		return 0;
		}
	string str=show(numer);
	char val[33]="";
	sprintf(val, "%d", atoi(str.c_str()));
	if(strcmp(str.c_str(), val)==0)
		return 1;
	return 0;
	}

/**** ****/
string Parser::getText()
	{
	return text;
	}
