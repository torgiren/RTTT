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
		GameEngineBase(uint16 size);
		virtual ~GameEngineBase();
		/**
		 * @brief Aktualny gracz
		 * @details Zwraca numer aktualnego gracza.
		 * @return Numer aktualnego gracza.
		 */
		uint16 ActPlayer() const;
		Planet& GetPlanet(const Vertex& src) const;
		uint16 GetSize() const;
	protected:
		std::set<uint16> itsPlayers;
		std::set<uint16>::iterator itsActPlayer;
		Planet*** itsPlanety;
		uint16 itsSize;
};
#endif
