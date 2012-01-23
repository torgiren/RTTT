#include <iostream>
#include <cstdlib>
#include "gameengine.h"
#include "planet.h"
using namespace std;
int main()
{
	srand(time(NULL));
	GameEngine silnik(4,4);
	int x,y,z;

	char c;
	int x1=-1,y1=-1,z1=-1;
	int x2=-1,y2=-1,z2=-1;
	int num;
	do
	{
		x1=-1;
		x2=-1;
		y1=-1;
		y2=-1;
		z1=-1;
		z2=-1;
		num=0;
		cin>>c;
		if(c=='m')
		{
			cin>>x1>>y1>>z1;
			cin>>x2>>y2>>z2;
			cin>>num;
			cout<<"Move: "<<silnik.Move(Vertex(x1,y1,z1),Vertex(x2,y2,z2),num)<<endl;
		}
		for(z=0;z<4;z++)
		{
			for(x=0;x<4;x++)
			{
				for(y=0;y<4;y++)
				{
					Planet& plan=silnik.GetPlanet(Vertex(x,y,z));
					plan.EndTurn();
					if(x2==x&&y2==y&&z2==z)
						cout<<"{";
					else if(x1==x&&y1==y&&z1==z)
						cout<<"[";
					else cout<<"(";
					cout<<plan.RetGracz()<<","<<plan.RetOkupant()<<","<<plan.RetJednostki()<<","<<plan.RetPoziom();
					if(x1==x&&y1==y&&z1==z)
						cout<<"] ";
					else if(x2==x&&y2==y&&z2==z)
						cout<<"} ";
					else cout<<") ";
				};
				cout<<"\n";
			};
			cout<<"********"<<endl;
		};
	}while(c!='q');

};
