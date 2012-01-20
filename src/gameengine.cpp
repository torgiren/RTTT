#include "gameengine.h"
#include <cstdlib>
#include <cstdio>
GameEngine::GameEngine(uint16 size, uint16 players):
itsSize(size),itsPlayers(players)
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
	for(x=0;x<itsPlayers;x++)
	{
		int px=rand()%itsSize;
		int py=rand()%itsSize;
		int pz=rand()%itsSize;
		if(itsPlanety[px][py][pz].RetGracz())
		{
			printf("miejsce %d %d %d jest zajete\n",px,py,pz);
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

