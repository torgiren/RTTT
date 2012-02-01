#include <iostream>
#include <string>
#include <cstdio>
#include <SDL/SDL_thread.h>
#include <SDL/SDL.h>
#include <vector>
#include <sstream>
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
int WindowFunc(void* null);
bool ServerReady=false;
bool EndGame=false;

#undef main

int main(int argc, char* argv[])
{
	srand(time(NULL));
	bool server=false;
	SDL_Thread* Server_thread=0;
	SDL_Thread* Window_thread=0;
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
	if(server)
	{
		int size,graczy;
		cout<<"Na jakim dużym obszarze będzie prowadzona bitwa?"<<endl;
		cin>>size;
		cout<<"Na ilu przewidujesz przeciwników?"<<endl;	
		cin>>graczy;
		cout<<"Tak jest... Przygotowuję odpowiedni obszar..."<<endl;
		GameEngine* silnik;
		silnik=new GameEngine(size,graczy);
		Server_thread=SDL_CreateThread(ServerFunc,(void*)silnik);
		cout<<"Uruchamiam server: ";
		while(!ServerReady)
		{
			cout<<".";
			SDL_Delay(100);
		};
		cout<<endl;
		MapSize=size;
		ip="127.0.0.1";
	}
	else
	{
		cout<<"Proszę wprowadzić cztery współrzędne bitwy (xxx.xxx.xxx.xxx):"<<endl;
		cin>>ip;
		MapSize=3;
	};
    Client* c=Client::create(ip,"2332");
	bool haveSize=false;
	cout<<"Przenoszę na pole bitwy..."<<endl;
	c->send("Hello");
	while(!haveSize)
	{
		string tmp=c->receive();
		cout<<"Czekam na rozmiar: "<<tmp<<endl;
		if(tmp.compare("empty"))
		{
			stringstream ss(tmp);
			string first;
			ss>>first;
			if(!first.compare("size"))
			{
				ss>>MapSize;
				cout<<"Wczytałem rozmiar: "<<MapSize<<endl;
				haveSize=true;
			};
		};
		SDL_Delay(100);
	};
	
	if(!WindowEngine::init(WindowEngine::SDL, WindowEngine::DELAY))
	{
		printf("Nie udało sie utworzyć okienka\n");
		return 100;
	}
	Drawing::setSurface(WindowEngine::getScreen());
	Screen::init();
	Screen::setSize(MapSize);
	Window_thread=SDL_CreateThread(WindowFunc,NULL);

//	SDL_Delay(1000);
//    Client* c=new Client(*SocketSingleton::get(),ip.c_str(), "2332");
	c->send("Hello");
	while(!EndGame)
	{
		cout<<"*"<<endl;
		string tmp=c->receive();
		cout<<"Otrzymalem: "<<tmp<<endl;
		if(!tmp.compare("empty"))
			SDL_Delay(1000);
		stringstream ss(tmp);
		string first;
		ss>>first;
		if(!first.compare("planet"))
		{
			cout<<"Aktualizacja planety"<<endl;
			int x,y,z;
			ss>>x>>y>>z;
			vector<pair<Vertex,Planet> > tmp;
			Planet plan=Planet::ToPlanet(ss.str());
			tmp.push_back(pair<Vertex,Planet>(Vertex(x,y,z),plan));
			cout<<"Aktualizacja w "<<x<<" "<<y<<" "<<z<<". Ma "<<plan.RetJednostki()<<" jednostek"<<" oraz gracz: "<<plan.RetGracz()<<endl;
			Screen::updateArea(tmp);
		};
//		c->send("client");
	};
//	GameEngineClient();
		
//	SDL_KillThread(Window_thread);
	Sprite::clear();
	WindowEngine::quit();
	if(server)
		SDL_KillThread(Server_thread);
	return 0;
};
int ServerFunc(void* engine)
{
	GameEngine* silnik=(GameEngine*)engine;
    Server* s = Server::create("2332");
	SDL_Delay(1000);
	ServerReady=true;
	stringstream ss;
	ss.str("");
	ss<<"size "<<silnik->GetSize();
	s->send(ss.str());
	int x,y,z;
	for(x=0;x<silnik->GetSize();x++)
	{
		for(y=0;y<silnik->GetSize();y++)
		{
			for(z=0;z<silnik->GetSize();z++)
			{
						ss.str("");
						ss<<"planet "<<x<<" "<<y<<" "<<z<<" "<<(string)silnik->GetPlanet(Vertex(x,y,z));
						s->send(ss.str());
			};
		};
	};
	int numGracz=0;
	while(true)
	{
		Message tmp=s->receive();
		cout<<"Server: "<<tmp.body()<<endl;
		string body=tmp.body();
		if(!body.compare("Hello"))
		{
		};
	};
	return 0;
};
int WindowFunc(void* null)
{
	while(WindowEngine::update())
	{
		Screen::update();
		Screen::draw();

		WindowEngine::print();
	}
	EndGame=true;
};
