#include "gameengineclient.h"
GameEngineClient::GameEngineClient(uint16 size):
GameEngineBase(size)
{
};
void GameEngineClient::PlanetUpdate(const Vertex& dst, const Planet& planet)
{
	GetPlanet(dst)=planet;
};
