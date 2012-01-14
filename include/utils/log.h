/*
 * log.h
 *
 *  Created on: 23-12-2011
 *      Author: crm
 */

#ifndef LOG_H_
#define LOG_H_

/**
 * @namespace Log
 * @brief Wypisywanie ladnie sformatowanych logow do podanego pliku (domyslnie stdout)
 */
namespace Log
	{
	/**
	 * @enum Poziomy logowania, dzialaja dokladnie tak, jak myslisz
	 */
	enum LogLvl {NONE=0x0, INFO=0x1, FAIL=0x2, OK=0x4, ALL=INFO|FAIL|OK};

	/**
	 * @brief Wypisuje wiadomosc informacyjna
	 * @details Dziala dokladnie tak, jak printf i inne funkcje tego typu
	 * @param[in] fmt Format wiadomosci
	 * @param[in] ... Zmienne
	 */
	void info(/*const char *loc, */const char *fmt, ...);
	/**
	 * @brief Wypisuje wiadomosc o bledzie
	 * @details Dziala dokladnie tak, jak printf i inne funkcje tego typu
	 * @param[in] fmt Format wiadomosci
	 * @param[in] ... Zmienne
	 */
	void fail(/*const char *loc, */const char *fmt, ...);
	/**
	 * @brief Wypisuje wiadomosc o sukcesie
	 * @details Dziala dokladnie tak, jak printf i inne funkcje tego typu
	 * @param[in] fmt Format wiadomosci
	 * @param[in] ... Zmienne
	 */
	void ok  (/*const char *loc, */const char *fmt, ...);

	/**
	 * @brief Zamyka plik, o ile nie jest to stdout
	 */
	void close();

	/**
	 * @brief Ustawia plik do ktorego wpisywane beda logi
	 * @param[in] sf Wskaznik na plik
	 */
	void setOut(FILE *sf);
	/**
	 * @brief Ustawia poziom logowanie
	 * @param[in] flag Flagi
	 * @related LogLvl
	 */
	void setLogLvl(int flag);
	}

#endif /* LOG_H_ */
