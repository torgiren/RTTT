#ifndef RESFILE_H
#define RESFILE_H

#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <cstring>
#include <zlib.h>

#include "parser.h"

class Resfile
	{
	private:
		enum Flags {NONE=0x0, COMPRESSED=0x1, ENCODED=0x2};		// Jeszcze miejsce na 5 flag, co by tu dodac~?

		struct HeadEntry
			{
			HeadEntry(): start(0), size(0), ucsize(0), flags(NONE) {};
			HeadEntry(unsigned int start, unsigned int size, unsigned int ucsize=0, unsigned char flags=NONE):
				start(start), size(size), ucsize(ucsize), flags(flags) {};

			unsigned int start, size;				/// \brief Poczatek i wielkosc pliku
			unsigned int ucsize;					/// \brief Wielkosc po rozpakowaniu
			unsigned char flags;					/// \brief Flagi
			//char *name;
			//std::string name;
			};

		std::fstream inFile;								// otwarty resfile
		std::string currFile;							// Nazwa aktualnie otwartego pliku
		unsigned int lastSize, resSize;				// Wielkosc ostatnio odczytanego pliku, wielkosc resfile
		unsigned char version;						// Wersja resfile, wywala bledy jesli sprobowano odczytac zla
		//bool uncompress;							// Jesli 0 to zwraca pliki nierozpakowane (czyli spakowane, o ile sa spakowane)

		std::map<std::string, HeadEntry *> headerMap;			// Mapa przyspieszajaca wyszukiwanie po nazwie
		std::vector<HeadEntry> header;					// Naglowek resfile

		char *bufor;								// Wskazniczek ktory zwracamy, nie czyscic

		char* load(HeadEntry& entry);
	public:
		Resfile();
		~Resfile();

		static Resfile& get();

		bool open(const std::string& resName);					/// \brief Otwiera resfile \a resName
		char* load(const std::string& resName, const std::string& fileName); /// \brief Wczytuje \a fileName z resfile \a resName
		char* load(const std::string& resName, unsigned int num);/// \brief Wczytuje \a num plik z resfile \a resName
		//char* load(const std::string& name);					/// \brief Wczytuje plik z resfile, format "sciezka_do_resfile:nazwa_pliku"
		char* load(const std::string& name);					/// \brief Wczytuje plik \aname z aktualnego resfile
		char* loadRes(const std::string& resName);				/// \brief Wczytuje caly resfile

		const char* getCurrFile() {return currFile.c_str();};
		bool checkFile(const std::string& fileName);			/// \brief Zwraca 1 jesli \a fileName istnieje w resfile
		bool checkFile(unsigned int num);						/// \brief Zwraca 1 jesli \a num plik istnieje w resfile

		unsigned int getSize(const std::string& fileName);		/// \brief Zwraca wielkosc \a fileName
		unsigned int getSize(unsigned int num);					/// \brief Zwraca wielkosc \a num pliku
		unsigned int getSize() {return resSize;};				/// \brief Zwraca wielkosc resfile
		unsigned int getLastSize() {return lastSize;};			/// \brief Zwraca wielkosc ostatnio pobranego pliku

		unsigned int getFileCount(const std::string& resName);	/// \brief Zwraca ilosc plikow w podanym resfile
		unsigned int getFileCount() {return header.size();};	/// \brief Zwraca ilosc plikow w aktualnie otwartym resfile
		//
		//const char* getFileName(unsigned int num) {};
		const std::string& getFileName(unsigned int num);
	};

#endif // RESFILE_H
