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
	Screen::setGameEngineClient(engine);
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
	stringstream ss;
	int numGracz=0;
	bool update=false;
	while(!silnik->IsEndGame())
	{
		update=false;
//		cout<<"Czekam"<<endl;
		Message tmp=s->receive();
		string body=tmp.body();
//		cout<<"Server: "<<body<<endl;
//		cout<<"Klient nr: "<<tmp.source()<<endl;
		stringstream ss(body);
		string first;
		ss>>first;
//		cout<<"First: "<<first<<endl;
		uint16 client=tmp.source();
		if(!first.compare("Hello"))
		{
			s->send("witam");
			cout<<"Nowy gracz"<<endl;
			++numGracz;
//			stringstream ss;
			stringstream ss;
			ss<<"player "<<silnik->AddPlayer(client);
//			cout<<"ss: "<<ss.str()<<endl;
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
			ss.str("");
			ss<<"act "<<silnik->ActPlayer();
			s->send(ss.str());
		}
	
		if(silnik->CanDoAction(client))
		{
			cout<<"Can do..."<<endl;
			if(!first.compare("move"))
			{
				update=true;
//				cout<<"Server: poruszam jednoski"<<endl;
				int x1,y1,z1,x2,y2,z2,num;
				ss>>x1>>y1>>z1>>x2>>y2>>z2>>num;
				Vertex src(x1,y1,z1);
				Vertex dst(x2,y2,z2);
//				cout<<x1<<" "<<y1<<" "<<z1<<" "<<x2<<" "<<y2<<" "<<z2<<endl;
				RETURNS::MOVE ret=silnik->Move(src,dst,num);
				switch(ret)
				{
					case RETURNS::TOO_MUCH:
						cout<<"Za duzo..."<<endl;
						break;
					case RETURNS::OUT_OF_AREA:
						cout<<"Za daleko"<<endl;
						break;
					case RETURNS::NOT_ANY:
						cout<<"Za malo"<<endl;
						break;
					case RETURNS::MOVE_OK:
						cout<<"Ok"<<endl;
						break;
					case RETURNS::MOVE_FIGHT:
						cout<<"Walka"<<endl;
						break;
				};
			}
			else if(!first.compare("end"))
			{
				update=true;
				silnik->EndTurn();
				ss.clear();
				ss<<"act "<<silnik->ActPlayer();
				s->send(ss.str());		
			};
		};


		if(update)
		{
			int x,y,z;
			for(x=0;x<silnik->GetSize();x++)
			{
				for(y=0;y<silnik->GetSize();y++)
				{
					for(z=0;z<silnik->GetSize();z++)
					{
								stringstream ss;
								ss<<"planet "<<x<<" "<<y<<" "<<z<<" "<<(string)silnik->GetPlanet(Vertex(x,y,z));
								s->send(ss.str());
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
