#ifndef __GAMEENGINECLIENT_H
#define __GAMEENGINECLIENT_H
#include "gameenginebase.h"
#include <string>
#include <sstream>
#include "Client.hpp"
#include "screen.h"
/**
 * @brief Klasa silnika gry dla klienta
 * @author Marcin TORGiren Fabrykowski
 */
class GameEngineClient: public GameEngineBase
{
	public:
		static GameEngineClient* Create(std::string ip)
		{
			Client* c=Client::create(ip.c_str(),"2330");	
			c->send("Hello");
			bool haveSize=false;
			bool haveNum=false;
			uint16 PlayerNum;
			uint16 MapSize;
			while(!haveSize||!haveNum)
			{
				std::string tmp=c->receive();
				cout<<"Czekam na nr i rozmiar: "<<tmp<<endl;
				if(tmp.compare("empty"))
				{
					std::stringstream ss(tmp);
					std::string first;
					ss>>first;
					if(!first.compare("player"))
					{
						ss>>PlayerNum;
//						cout<<"Wczytałem numer gracza: "<<PlayerNum<<endl;
						haveNum=true;
						Screen::setPlayerID(PlayerNum+1);
					}
					if(!first.compare("size"))
					{
						ss>>MapSize;
//						cout<<"Wczytałem rozmiar: "<<MapSize<<endl;
						haveSize=true;
					};
				};
				SDL_Delay(100);
			};
			return new GameEngineClient(MapSize,PlayerNum,c);
		};
		
		void MainLoop();
		void PlanetUpdate(const Vertex& dst, const Planet& planet);
		void EndGame();
	private:
		GameEngineClient(uint16 size,uint16 num,Client* client);
		Client* itsC;
		uint16 itsPlayerNum;
		bool itsEndGame;
};
#endif
