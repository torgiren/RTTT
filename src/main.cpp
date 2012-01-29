#include <iostream>
#include <string>
#include <cstdio>
#include <SDL/SDL_thread.h>
#include <SDL/SDL.h>
#include <vector>
#include "gameengine.h"
#include "gameengineclient.h"
#include "Participant.hpp"
#include "Room.hpp"
#include "Message.hpp"
#include "Session.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "sprite.h"
#include "text.h"
#include "drawing.h"
#include "screen.h"
using namespace std;
int ServerFunc(void* engine);
int main(int argc, char* argv[])
{
	bool server=false;
	SDL_Thread* Server_thread=0;
	cout<<"Witaj poruczniku...\nPlanujesz swoją własną bitwę czy dołączyć się do innej?\n";
menu:
	cout<<"1) Własna bitwa\n";
	cout<<"2) Przyłączenie sie do istniejącej"<<endl;
	char opt[255];
	cin>>opt;
	switch(opt[0])
	{
		case '1':
			server=true;
			break;
		case '2':
			server=false;
			break;
		default:
			cout<<"Jakieś <trzask> zakłócenia <trzask>. Proszę powtórzyć wybór..."<<endl;
			goto menu;
	};
	string ip;
	int MapSize=3;
	GameEngine* silnik;
	if(server)
	{
		int size,graczy;
		cout<<"Na jakim dużym obszarze będzie prowadzona bitwa?"<<endl;
		cin>>size;
		cout<<"Na ilu przewidujesz przeciwników?"<<endl;	
		cin>>graczy;
		cout<<"Tak jest... Przygotowuję odpowiedni obszar..."<<endl;
		silnik=new GameEngine(size,graczy);
		Server_thread=SDL_CreateThread(ServerFunc,(void*)silnik);
		MapSize=size;
		ip="127.0.0.1";
	}
	else
	{
		cout<<"Proszę wprowadzić cztery współrzędne bitwy (xxx.xxx.xxx.xxx):"<<endl;
		cin>>ip;
		Screen::setSize(3);
	};
	
	if(!WindowEngine::init(WindowEngine::SDL, WindowEngine::DELAY))
	{
		printf("Nie udalo sie stworzyc okienka\n");
		return 100;
	}
	Drawing::setSurface(WindowEngine::getScreen());
	Screen::init();
	Screen::setSize(silnik->GetSize());
	{
		vector<pair<Vertex,Planet> >plan;
		int x,y,z;
		for(x=0;x<MapSize;x++)
		{
			for(y=0;y<MapSize;y++)
			{
				for(z=0;z<MapSize;z++)
				{
					Vertex v(x,y,z);
					plan.push_back(pair<Vertex,Planet>(v,silnik->GetPlanet(v)));
				};
			};
		};
		Screen::updateArea(plan);
	};
	while(WindowEngine::update())
	{
		Screen::update();
		Screen::draw();

		WindowEngine::print();
	}

	Sprite::clear();
	WindowEngine::quit();
//	SDL_Delay(1000);
//    Client* c=new Client(*SocketSingleton::get(),ip.c_str(), "2332");
//	GameEngineClient();
	if(server)
		SDL_WaitThread(Server_thread,NULL);
	return 0;
};
int ServerFunc(void* engine)
{
	return 0;
};
