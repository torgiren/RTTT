#ifndef __GAMEENGINEBASE_H
#define __GAMEENGINEBASE_H
#include <set>
#include <string>
#include "consts.h"
#include "vertex.h"
#include "planet.h"
class GameEngineBase
{
	public:
		/**
		 * @brief Konstruktor tworzący pole bitwy
		 * @details Konstruktor klasy bazowej dla Silnika gry i silnika klienta. TWorzy on pole bitwy o zadanym rozmiarze. Pole ma postać sześciany o rozmiarze size
		 * @param size Rozmiar boku sześcianu pola bitwy liczony w ilości planet
		 */
		GameEngineBase(uint16 size);
		virtual ~GameEngineBase();
		/**
		 * @brief Aktualny gracz
		 * @details Zwraca numer aktualnego gracza.
		 * @return Numer aktualnego gracza.
		 */
		uint16 ActPlayer() const;
		/**
		 * @brief Zwraca planetę o zadanym położeniu
		 * @details Zwraca referencję do planety znajdującej się w położeniu Vertexu podanego jako argument
		 * @param src Vertex wskazujący na położenie planety która ma być zwrócona
		 * @return Referencja do planety z zadanego położenia
		 */
		Planet& GetPlanet(const Vertex& src) const;
		/**
		 * @brief Zwraca rozmiar pola bitwy
		 * @details Zwraca rozmiar pola bitwy
		 * @return Rozmair pola bitwy
		 */
		uint16 GetSize() const;
	protected:
		std::set<uint16> itsPlayers;
		std::set<uint16>::iterator itsActPlayer;
		Planet*** itsPlanety;
		uint16 itsSize;
};
#endif
