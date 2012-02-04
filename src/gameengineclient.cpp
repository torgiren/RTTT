#include "gameengineclient.h"
#include "Client.hpp"
GameEngineClient::GameEngineClient(uint16 size,uint16 num,Client* client):
GameEngineBase(size),itsC(client),itsPlayerNum(num),itsEndGame(false)
{
};
void GameEngineClient::PlanetUpdate(const Vertex& dst, const Planet& planet)
{
	GetPlanet(dst)=planet;
};
void GameEngineClient::MainLoop()
{
	while(!itsEndGame)
	{
		string tmp=itsC->receive();
		if(!tmp.compare("empty"))
		{
			SDL_Delay(1000);
			continue;
		};
		cout<<"Otrzymałem(client): "<<tmp<<endl;
		stringstream ss(tmp);
		string first;
		ss>>first;
		if(!first.compare("planet"))
		{
			int x,y,z;
			ss>>x>>y>>z;
			vector<pair<Vertex,Planet> > tmp;
			Planet plan=Planet::ToPlanet(ss.str());
			tmp.push_back(pair<Vertex,Planet>(Vertex(x,y,z),plan));
			Screen::updateArea(tmp);
		};
	};
};
void GameEngineClient::EndGame()
{
	itsEndGame=true;
};
void GameEngineClient::SendMove(Vertex src, Vertex dst, uint16 num)
{
	stringstream ss;
	ss<<"move "<<(string)src<<" "<<(string)dst<<" "<<num;
	itsC->send(ss.str());
};
void GameEngineClient::SendEndTurn()
{
	itsC->send("end");
};
