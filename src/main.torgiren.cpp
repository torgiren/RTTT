#include <iostream>
#include <cstdlib>
#include "gameengine.h"
#include "planet.h"
using namespace std;
int main()
{
	srand(time(NULL));
	int x=0;
	for(x=0;x<10;x++)
	{
		Planet ziemia;
//		cout<<"Broniacy ma: "<<ziemia.RetJednostki()<<endl;
		ziemia.Atak(10,0);
	};
	cout<<"Hello"<<endl;
	GameEngine eng(5,5);
};
