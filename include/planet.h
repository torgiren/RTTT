#ifndef __PLANET_H
#define __PLANET_H
#include "consts.h"
#include <list>
#include <vector>
/**
 * @brief Klasa planety
 * @details Opisuje właściwości planety - elementrarnej jednoski przestrzeni
 * @author Marcin TORGiren Fabrykowski
 */
class Planet
{
	friend class GameEngine;
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
		 * @details Zwraca aktualny poziom okupacji. Wartość OCCUPY_MAX oznacza, ze planeta nie jest juz okupowana i jest w pełni przejęta
		 * @return Poziom okupacji, bądź OCCUPY_MAX w przypadku gdy planeta nie jest okupowana i jest w pełni przejęta
		 */
		uint16 RetPoziom() const;
		/**
		 * @brief Zwraca ilosc jednostek na planecie
		 * @defails Funkcja wraca liczbę floty znajdującej się na planecie. Jeśli planeta nie jest okupowana, jest to liczba jednostek gracza będącego właścicielem, natomiast w przypadku okupacji, jest to liczba jednostek okupanta
		 * @return Liczba jednostek właściciela planety. W przypadku gdy planeta jest okupowana, to jest liczba jednostek okupanta
		 */
		uint16 RetJednostki() const;
		/**
		 * @brief Przeprowadza atak na planete
		 * @detail Przeprowadza atak zadanej ilości jednostek na planete.
		 * @param ile Liczba jednostek wroga, biąrąca udział w ataku
		 * @param kogo Numer gracza który przeprowadza atak
		 * @return Zwraca wektor reprezentujący kolejne starcia, zawierający pary wektorów rzutów 
		 * W przypadku mniejszej ilości jednostek po którejś ze stron, w miejsce rzutu wstawiana jest wartość 0
		 */
		FightResult Atak(uint16 ile, uint16 kogo);
		/**
		 * @brief Ustawia nowego właściciela planety
		 * @details Metoda która ustawia nowego właściciela planety
		 * @param gracz Numer gracza będącego nowym właścicielem
		 */
		void SetPlayer(uint16 gracz);
		/**
		 * @brief Kończy turę na danej planecie
		 * @details W przypadku okupowania planety następuje zdobywanie/zdejmowanie flagi.<br/>
		 * W przypadku posiadanych planet, następuje tworzenie nowych jednostek
		 */
		void EndTurn();
		RETURNS::MOVE Zabierz(uint16 ile);
		void Dodaj(uint16 ile);
	private:
		/**
		 * @brief Symuluje zdobywanie flagi na okupowanej planecie
		 * @details Jeśli planeta jest w posiadaniu innego gracza to jego flaga jest zdejmowana o poziom niżej, natomiast jeśli planeta jest neutralna bądź w posiadaniu gracza, wtedy flaga podnoszona jest o jeden poziom
		 */
		void Flaga();
	private:
		void Jednostki();
		uint16 itsGracz;
		uint16 itsFlagaPoziom;
		uint16 itsFlagaGracz;
		uint16 itsJednostki;
		uint16 itsOkupant;
};
#endif
