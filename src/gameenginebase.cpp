#include "gameenginebase.h"
#include <stdio.h>
GameEngineBase::GameEngineBase(uint16 size):
itsSize(size)
{
	itsPlanety=new Planet**[itsSize];
};
GameEngineBase::~GameEngineBase()
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
//	printf("dest\n");
};
uint16 GameEngineBase::ActPlayer() const
{
	return *itsActPlayer;
};
Planet& GameEngineBase::GetPlanet(const Vertex& src) const
{
	return itsPlanety[(int)src.x][(int)src.y][(int)src.z];
};
uint16 GameEngineBase::GetSize() const
{
	return itsSize;
};
