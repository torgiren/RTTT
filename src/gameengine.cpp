#include "gameengine.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;
GameEngine::GameEngine(uint16 size, uint16 players):
itsSize(size)
{
	itsPlanety=new Planet**[itsSize];
	int x,y;
	for(x=0;x<players;x++)
	{
		itsPlayers.insert(x+1);
	};
	itsActPlayer=itsPlayers.begin();
	for(x=0;x<itsSize;x++)
	{
		itsPlanety[x]=new Planet*[itsSize];
		for(y=0;y<itsSize;y++)
		{
			itsPlanety[x][y]=new Planet[itsSize];
		};
	};
	for(x=1;x<=(int)itsPlayers.size();x++)
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
				uint16 gracz=itsPlanety[x][y][z].RetGracz();
				uint16 okup=itsPlanety[x][y][z].RetOkupant();
				uint16 act=ActPlayer();
				if(gracz==act||okup==act)
				{
					RETURNS::ENDTURN result=itsPlanety[x][y][z].EndTurn();
					cout<<"Result: "<<result<<endl;
					if(result&RETURNS::PLAYER_IN)
						cout<<"Planeta została podbita"<<endl;
				}
			};
		};
	}
	return NextPlayer();
};
uint16 GameEngine::ActPlayer() const
{
	return *itsActPlayer;
};
uint16 GameEngine::NextPlayer()
{
	if(++itsActPlayer==itsPlayers.end()) itsActPlayer=itsPlayers.begin();
	return *itsActPlayer;
};
RETURNS::MOVE GameEngine::Move(const Vertex& src, const Vertex& dst, uint16 num)
{
	Planet& Psrc=GetPlanet(src);
	Planet& Pdst=GetPlanet(dst);
	if(CanMoveFrom(Psrc,ActPlayer()))
	{
		RETURNS::MOVE wynik;	
		wynik=Psrc.Zabierz(num);
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
		return wynik;
	};
	return RETURNS::NOT_ANY;
};
Planet& GameEngine::GetPlanet(const Vertex& src) const
{
	return itsPlanety[(int)src.x][(int)src.y][(int)src.z];
};
void GameEngine::RemovePlayer(uint16 player)
{
	if(*itsActPlayer==player)
		itsActPlayer--;
	itsPlayers.erase(player);
};
uint16 GameEngine::GetSize() const
{
	return itsSize;
};
bool GameEngine::CanMoveFrom(Planet& planeta, uint16 gracz) const
{
	uint16 okup=planeta.RetOkupant();
	if(okup)
	{
		if(okup==gracz)
			return true;
		return false;
	}
	else
	{
		if(planeta.RetGracz()==gracz)
			return true;
		return false;
	};
};
bool IsWinning(const Vertex& src)
{
	return true;
};


