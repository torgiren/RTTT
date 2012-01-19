#ifndef __PLANET_H
#define __PLANET_H
#include "consts.h"
/**
 * @brief Klasa planety
 * @details Opisuje właściwości planety - elementrarnej jednoski przestrzeni
 * @author Marcin TORGiren Fabrykowski
 */
class Planet
{
	public:
		/**
		 * @brief Tworzy planete
		 * @details Konstruktor. Tworzy neutralna planete z losowa (od 0 do 9) liczbą jednostek
		 */
		Planet();
		/**
		 * @brief Zwraca numer gracza-właściciela planety
		 * @details Zwraca numer gracza który jest aktualnie posiadaczem planety. Planeta może byc okupowana przez innego gracza i wciąż być w posiadaniu starego właściciela
		 * @return Zwraca numer gracza który jest właścicielem planety, bądź NULL jeśli takiego nie ma
		 */
		uint16 RetGracz() const;
		/**
		 * @brief Zwraca numer gracza-okupanta planety
		 * @details Zwraca numer gracza który jest aktualnie okupantem planety
		 * @return Numer gracza który okupuje planete, badź NULL jeśli takowego nie ma
		 */
		uint16 RetOkupant() const;
		/**
		 * @brief Zwracam poziom zaawansowania okupacji
		 * @details Zwraca aktualny poziom okupacji. Wartość OCUPY_MAX oznacza, ze planeta nie jest juz okupowana i jest w pełni przejęta
		 * @return Poziom okupacji, bądź OCUPY_MAX w przypadku gdy planeta nie jest okupowana i jest w pełni przejęta
		 */
		uint16 RetPoziom() const;
		/**
		 * @brief Zwraca ilosc jednostek na planecie
		 * @defails Funkcja wraca liczbę floty znajdującej się na planecie. Jeśli planeta nie jest okupowana, jest to liczba jednostek gracza będącego właścicielem, natomiast w przypadku okupacji, jest to liczba jednostek okupanta
		 * @return Liczba jednostek właściciela planety. W przypadku gdy planeta jest okupowana, to jest liczba jednostek okupanta
		 */
		uint16 RetJednostki() const;
	private:
		uint16 itsGracz;
		uint16 itsPoziom;
		uint16 itsJednostki;
};
#endif
