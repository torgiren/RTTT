#ifndef __PLANET_H
#define __PLANET_H
#include "consts.h"
#include <list>
#include <vector>
#include <string>
/**
 * @brief Klasa planety
 * @details Opisuje właściwości planety - elementarnej jednostki przestrzeni
 * @author Marcin TORGiren Fabrykowski
 */
class Planet
{
	public:
		/**
		 * @brief Tworzy planetę
		 * @details Konstruktor. Tworzy neutralna planetę z losowa (od 0 do 9) liczbą jednostek
		 */
		Planet();
		/**
		 * @brief Zwraca numer gracza-właściciela planety
		 * @details Zwraca numer gracza który jest aktualnie posiadaczem planety. Planeta może być okupowana przez innego gracza i wciąż być w posiadaniu starego właściciela
		 * @return Zwraca numer gracza który jest właścicielem planety, bądź NULL jeśli takiego nie ma
		 */
		uint16 RetGracz() const;
		/**
		 * @brief Zwraca numer gracza-okupanta planety
		 * @details Zwraca numer gracza który jest aktualnie okupantem planety
		 * @return Numer gracza który okupuje planetę, bądź NULL jeśli takowego nie ma
		 */
		uint16 RetOkupant() const;
		/**
		 * @brief Zwracam poziom zaawansowania okupacji
		 * @details Zwraca aktualny poziom okupacji. Wartość OCCUPY_MAX oznacza, ze planeta nie jest już okupowana i jest w pełni przejęta
		 * @return Poziom okupacji, bądź OCCUPY_MAX w przypadku gdy planeta nie jest okupowana i jest w pełni przejęta
		 */
		uint16 RetPoziom() const;
		/**
		 * @brief Zwraca ilość jednostek na planecie
		 * @details Funkcja wraca liczbę floty znajdującej się na planecie. Jeśli planeta nie jest okupowana, jest to liczba jednostek gracza będącego właścicielem, natomiast w przypadku okupacji, jest to liczba jednostek okupanta
		 * @return Liczba jednostek właściciela planety. W przypadku gdy planeta jest okupowana, to jest liczba jednostek okupanta
		 */
		uint16 RetJednostki() const;
		/**
		 * @brief Przeprowadza atak na planetę
		 * @details Przeprowadza atak zadanej ilości jednostek na planetę.
		 * @param ile Liczba jednostek wroga, biorąca udział w ataku
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
		RETURNS::ENDTURN EndTurn();
		/**
		 * @brief Zabiera z planety zadaną liczbę jednostek
		 * @details Zmniejsza liczbę jednostek na danej planecie o zadaną zwartość. Sprawdza tylko czy zadana wartość jest mniejsza bądź równa ilości jednostek na planecie
		 * @param ile Zadana ilość jednostek do zabrania
		 * @return Zwraca status operacji
		 */
		RETURNS::MOVE Zabierz(uint16 ile);
		/**
		 * @brief Dodaje jednostki do planety
		 * @details Zwiększa liczbę jednostek na planecie o zadaną ilość
		 * @param ile Liczba jednostek które zostaną dodane do garnizonu planety
		 */
		void Dodaj(uint16 ile);
		/**
		 * @brief Konwertuje planetę do postaci stringa
		 * @details Konwertuje obiekt klasy Planeta do postaci stringa. Format to:<br/>Nr_gracza Poziom_flagi Nr_Gracza_Posiadacza Liczba_Jednostek Nr_Gracza_Okupanta
		 * @return String reprezentujący tą planete
		 * @see ToPlanet(std::string str)
		 */
		std::string ToString();
		/**
		 * @brief Konwertuje planetę do postaci stringa 
		 * @details To samo to ToString();
		 * @see ToPlanet(std::string str)
		 */
		operator std::string();
		/**
		 * @brief Tworzy planetę na podstawie stringa
		 * @details Tworzy planetę na podstawie stringa o formacie: Nr_gracza Poziom_flagi Nr_Gracza_Posiadacza Liczba_Jednostek Nr_Gracza_Okupanta
		 * @return Klasa planety powstała po interpretacji stringa
		 * @see ToString()
		 */
		static Planet ToPlanet(std::string str);
	private:
		/**
		 * @brief Symuluje zdobywanie flagi na okupowanej planecie
		 * @details Jeśli planeta jest w posiadaniu innego gracza to jego flaga jest zdejmowana o poziom niżej, natomiast jeśli planeta jest neutralna bądź w posiadaniu gracza, wtedy flaga podnoszona jest o jeden poziom
		 */
		RETURNS::ENDTURN Flaga();
		bool Jednostki();
		uint16 itsGracz;
		uint16 itsFlagaPoziom;
		uint16 itsFlagaGracz;
		uint16 itsJednostki;
		uint16 itsOkupant;
};
#endif
