#include "gameengine.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;
GameEngine::GameEngine(uint16 size, uint16 players):
itsSize(size),itsPlayers(players),itsActPlayer(1)
{
	itsPlanety=new Planet**[itsSize];
	int x,y;
	for(x=0;x<itsSize;x++)
	{
		itsPlanety[x]=new Planet*[itsSize];
		for(y=0;y<itsSize;y++)
		{
			itsPlanety[x][y]=new Planet[itsSize];
		};
	};
	for(x=1;x<=itsPlayers;x++)
	{
		int px=rand()%itsSize;
		int py=rand()%itsSize;
		int pz=rand()%itsSize;
		if(itsPlanety[px][py][pz].RetGracz())
		{
			printf("miejsce %d %d %d jest zajete\n",px,py,pz);
			x--;
			continue;
		}
		else
		{
			itsPlanety[px][py][pz].SetPlayer(x);
			printf("umieszczam gracz %d na miejscu %d %d %d\n",x,px,py,pz);
		};
	};
};
GameEngine::~GameEngine()
{	
	int x,y;
	for(x=0;x<itsSize;x++)
	{
		for(y=0;y<itsSize;y++)
		{
			delete [] itsPlanety[x][y];
		}
		delete [] itsPlanety[x];
	};
	delete [] itsPlanety;
};
uint16 GameEngine::EndTurn()
{
	int x,y,z;
	for(x=0;x<itsSize;x++)
	{
		for(y=0;y<itsSize;y++)
		{
			for(z=0;z<itsSize;z++)
			{
				itsPlanety[x][y][z].EndTurn();
			};
		};
	}
	return NextPlayer();
};
uint16 GameEngine::ActPlayer() const
{
	return itsActPlayer;
};
uint16 GameEngine::NextPlayer()
{
	if(++itsActPlayer>=itsPlayers) itsActPlayer=1;
	return itsActPlayer;
};
RETURNS::MOVE GameEngine::Move(const Vertex& src, const Vertex& dst, uint16 num)
{
	Planet& Psrc=GetPlanet(src);
	Planet& Pdst=GetPlanet(dst);
	RETURNS::MOVE wynik;	
	if(Psrc.RetGracz())
	{
		wynik=Psrc.Zabierz(num);
		//TODO zrobić przesyłanie jednostek, a w przypadku ataku jakoś zwracanie logu z walki
		if(wynik==RETURNS::MOVE_OK)
		{
			cout<<"zabrane"<<endl;
			if((Psrc.RetGracz()==Pdst.RetGracz())&&(!Pdst.RetOkupant()))
			{
				cout<<"warunek 1"<<endl;
				Pdst.Dodaj(num);
				return RETURNS::MOVE_OK;
			};
			if((Psrc.RetGracz()!=Pdst.RetGracz())&&(Psrc.RetGracz()==Pdst.RetOkupant()))
			{
				cout<<"warunek 2"<<endl;
				Pdst.Dodaj(num);
				return RETURNS::MOVE_OK;
			};
			if((Psrc.RetGracz()!=Pdst.RetGracz())&&(Psrc.RetGracz()!=Pdst.RetOkupant()))
			{
				cout<<"warunek 3"<<endl;
				itsLastFight=Pdst.Atak(num,Psrc.RetGracz());		
				return RETURNS::MOVE_FIGHT;
			};
		}
	};
	return wynik;
};
Planet& GameEngine::GetPlanet(const Vertex& src)
{
	return itsPlanety[(int)src.x][(int)src.y][(int)src.z];
};
