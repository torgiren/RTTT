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
GameEngineClient* engine=NULL;
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
	cout<<"Uruchamian clienta"<<endl;
	engine=GameEngineClient::Create(ip);
//    Client* c=Client::create(ip,"2332");
	

	cout<<"Przenoszę na pole bitwy..."<<endl;
	if(!WindowEngine::init(WindowEngine::SDL, WindowEngine::DELAY))
	{
		printf("Nie udało sie utworzyć okienka\n");
		return 100;
	}
	Screen::init();
	Screen::setSize(engine->GetSize());
	Drawing::setSurface(WindowEngine::getScreen());
	Window_thread=SDL_CreateThread(WindowFunc,NULL);

	engine->MainLoop();
//    Client* c=new Client(*SocketSingleton::get(),ip.c_str(), "2332");
	Sprite::clear();
	WindowEngine::quit();
	if(server)
		SDL_KillThread(Server_thread);
	return 0;
};
int ServerFunc(void* engine)
{
	GameEngine* silnik=(GameEngine*)engine;
    Server* s = Server::create("2330");
	ServerReady=true;
	cout<<"Ja zyje..."<<endl;
	stringstream ss;
	int numGracz=0;
	while(true)
	{
//		cout<<"Czekam"<<endl;
		Message tmp=s->receive();
//		cout<<"Server: "<<tmp.body()<<endl;
//		cout<<"Klient nr: "<<tmp.source()<<endl;
		string body=tmp.body();
		if(!body.compare("Hello"))
		{
			numGracz++;
			uint16 client=tmp.source();
			ss.str("");
			ss<<"player "<<client;
			s->send(client,ss.str());
			ss.str("");
			ss<<"size "<<silnik->GetSize();
			s->send(client,ss.str());
			int x,y,z;
			for(x=0;x<silnik->GetSize();x++)
			{
				for(y=0;y<silnik->GetSize();y++)
				{
					for(z=0;z<silnik->GetSize();z++)
					{
								ss.str("");
								ss<<"planet "<<x<<" "<<y<<" "<<z<<" "<<(string)silnik->GetPlanet(Vertex(x,y,z));
								s->send(client,ss.str());
					};
				};
			};
		};
	};
	cout<<"i po serverze..."<<endl;
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
	engine->EndGame();
};
