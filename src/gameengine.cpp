#include "gameengine.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>
using namespace std;
GameEngine::GameEngine(uint16 size, uint16 players):
GameEngineBase(size),itsEndGame(false)
{
//	itsPlanety=new Planet**[itsSize];
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
//					cout<<"Result: "<<result<<endl;
					if(result&RETURNS::PLAYER_IN)
					{
//						gracz=itsPlanety[x][y][z].RetGracz();
						cout<<"Planeta została podbita"<<endl;
						if(IsWinning(Vertex(x,y,z)))
						{
							cout<<"KONIEC GRY!!!!!!"<<endl;
							itsEndGame=true;
						};
					}
					if(result&RETURNS::PLAYER_OUT)
					{
						cout<<"Gracz na planecie obalony"<<endl;
						if(IsWinning(okup))
						{
							cout<<"KONIEC GRY PRZEZ POKONANIE!!!!!"<<endl;
							itsEndGame=true;
						};
					};
				}
			};
		};
	}
	return NextPlayer();
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
//			cout<<"zabrane"<<endl;
			if((Psrc.RetGracz()==Pdst.RetGracz())&&(!Pdst.RetOkupant()))
			{
//				cout<<"warunek 1"<<endl;
				Pdst.Dodaj(num);
				return RETURNS::MOVE_OK;
			};
			if((Psrc.RetGracz()!=Pdst.RetGracz())&&(Psrc.RetGracz()==Pdst.RetOkupant()))
			{
//				cout<<"warunek 2"<<endl;
				Pdst.Dodaj(num);
				return RETURNS::MOVE_OK;
			};
			if((Psrc.RetGracz()!=Pdst.RetGracz())&&(Psrc.RetGracz()!=Pdst.RetOkupant()))
			{
//				cout<<"warunek 3"<<endl;
				itsLastFight=Pdst.Atak(num,Psrc.RetGracz());		
				return RETURNS::MOVE_FIGHT;
			};
		}
		return wynik;
	};
	return RETURNS::NOT_ANY;
};
void GameEngine::RemovePlayer(uint16 player)
{
	if(*itsActPlayer==player)
		itsActPlayer--;
	itsPlayers.erase(player);
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
bool GameEngine::IsWinning(const Vertex& src) const
{
	int x=src.x;
	int y=src.y;
	int z=src.z;
	uint16 gracz=itsPlanety[x][y][z].RetGracz();
	int i;	
	int planet=0;
	for(planet=0,i=0;i<GetSize();i++)
	{
		if(itsPlanety[x][i][z].RetGracz()==gracz)
			planet++;	
	};
	if(planet==GetSize())
		return true;
	for(planet=0,i=0;i<GetSize();i++)
	{
		if(itsPlanety[x][y][i].RetGracz()==gracz)
			planet++;	
	};
	if(planet==GetSize())
		return true;
	for(planet=0,i=0;i<GetSize();i++)
	{
		if(itsPlanety[i][y][z].RetGracz()==gracz)
			planet++;	
	};
	if(planet==GetSize())
		return true;

	return false;
};
bool GameEngine::IsWinning(const uint16 gracz) const
{
	int x,y,z;
	for(x=0;x<GetSize();x++)
	{
		for(y=0;y<GetSize();y++)
		{
			for(z=0;z<GetSize();z++)
			{
				uint16 tmpgracz=itsPlanety[x][y][z].RetGracz();
				if(tmpgracz&&(tmpgracz!=gracz))
					return false;
			};
		};
	};
	return true;
};
uint16 GameEngine::AddPlayer(uint16 socket_id)
{
	static uint16 act=1;	
	itsPlayersMap[socket_id]=act;
	return act++;
};
bool GameEngine::CanDoAction(uint16 socket_id)
{
	return ActPlayer()==itsPlayersMap[socket_id];
};
bool GameEngine::IsEndGame() const
{
	return itsEndGame;
};
