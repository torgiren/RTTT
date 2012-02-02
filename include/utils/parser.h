#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cstdio>

/**
 * @class Parser
 * @brief Parser tekstu
 * @details Dzieli tekst używając podanego zestawu znaków na elementy. Pozwala na ich odczyt i modyfikację.
 * Przykład:
 *  tekst: <i>Rena is mai waifu</i>
 *  Parser[3] zwróci <i>waifu</i>
 *
 *  @author crm
 */
class Parser
	{
	private:
		std::vector <int> elementy;
		//string element;		// Pozbylem sie jednego stringa, wooo~ o;
		std::string text;
		std::string delimiter;
	public:
		Parser(std::string text="", std::string delim=" \t");
		~Parser();
		/// @brief Przypisanie tekstu
		Parser& operator=(std::string);
		/// @brief Przypisanie tekstu
		Parser& operator=(const char *);
		/// @brief Zwraca element na podanej pozycji
		std::string operator[] (int);
		/// @brief Wypisuje zawartość parsera
		operator const char*();
		/// @brief Czyści zawartość parsera
		void destroy();
		/// @brief Przypisanie tekstu
		void setText(std::string);
		/// @brief Ustawienie znaków oddzielających
		void setDelimiter(std::string);
		/// @brief Parsowanie tekstu. Wywoływane automatycznie po przypisaniu.
		void parse();
		/// @brief Zwraca ilość elementów
		int count();
		/// @brief Zwraca element na podanej pozycji
		std::string show(int);
		/// @brief Kasuje element z podanej pozucji
		void del(int);
		/// @brief Wstawia tekst po podanym elemencie
		void ins(int, std::string);
		/// @brief Zastępuje element podanym tekstem
		void swap(int, std::string);
		/// @brief Zwraca pozycję na której znajduje się podany tekst. Zwraca -1 jeśli nie znaleziono.
		int find(std::string);
		int val(int);
		float valFloat(int);
		bool isVal(int);

		std::string getText();
	};

#endif // PARSER_H
