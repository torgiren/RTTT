#ifndef __GAMEENGINECLIENT_H
#define __GAMEENGINECLIENT_H
#include "gameenginebase.h"
/**
 * @brief Klasa silnika gry dla klienta
 * @author Marcin TORGiren Fabrykowski
 */
class GameEngineClient: public GameEngineBase
{
	public:
		GameEngineClient(uint16 size);
		void PlanetUpdate(const Vertex& dst, const Planet& planet);
	private:
};
#endif
