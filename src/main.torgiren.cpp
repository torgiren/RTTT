#include <iostream>
#include <cstdlib>
#include "gameengine.h"
#include "planet.h"
using namespace std;
int main()
{
	srand(time(NULL));
	int x;
//	for(x=0;x<10;x++)
	{
		Planet ziemia;
		cout<<"planeta nalezy to: "<<ziemia.RetGracz()<<endl;
		cout<<"okupant: "<<ziemia.RetOkupant()<<endl;
		cout<<"Walka"<<endl;
//		cout<<"Broniacy ma: "<<ziemia.RetJednostki()<<endl;
		ziemia.Atak(15,3);
		int y=0;
		for(y=0;y<8;y++)
		{
			cout<<"tura: "<<y<<endl;
			cout<<"planeta nalezy to: "<<ziemia.RetGracz()<<endl;
			cout<<"okupant: "<<ziemia.RetOkupant()<<endl;
			cout<<"poziom: "<<ziemia.RetPoziom()<<endl;
			cout<<"Jednostek: "<<ziemia.RetJednostki()<<endl;
			ziemia.EndTurn();
			cout<<"@@@@@@@@@"<<endl;
		}
		cout<<"**********"<<endl;
	};
	cout<<"Hello"<<endl;
	GameEngine eng(2,6);
	cout<<"*********"<<endl;
	eng.EndTurn();
};
