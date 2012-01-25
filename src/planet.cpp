#include "planet.h"
#include <cstdlib>
#include <stdio.h>
#include <algorithm>
#include <iostream>
using namespace std;
Planet::Planet():
itsGracz(0),itsFlagaPoziom(0),itsOkupant(0)
{
	itsJednostki=8;
//	itsJednostki=rand()%5+5;
};
uint16 Planet::RetGracz() const
{
	return itsGracz;
};
uint16 Planet::RetOkupant() const
{
	return itsOkupant;
};
uint16 Planet::RetPoziom() const
{
	return itsFlagaPoziom;
};
uint16 Planet::RetJednostki() const
{
	return itsJednostki;
};
FightResult Planet::Atak(uint16 ile, uint16 kogo)
{
	FightResult wynik;
	int x=0;
	while(ile>0&&itsJednostki>0)
	{
		std::vector<uint16> atak;
		std::vector<uint16> obrona;
		for(x=0;x<(ile>3?3:ile);x++)
			atak.push_back(rand()%6+1);
		sort(atak.begin(),atak.end());
//		atak.sort();
//		atak.reverse();
		for(x=0;x<(itsJednostki>3?3:itsJednostki);x++)
			obrona.push_back(rand()%6+1);
		sort(obrona.begin(),obrona.end());
//		obrona.sort();
//		obrona.reverse();

		wynik.push_back(FightResultRow(atak,obrona));
		while(obrona.size()&&atak.size())
		{
//			printf("Rzuty: %d %d\n",atak.back(),obrona.back());
			if(atak.back()>obrona.back())
			{
				itsJednostki--;
//				printf("atakujacy wygrywa\n");
			}
			else
			{
//				printf("broniacy wygrywa\n");
				ile--;
			};
			obrona.pop_back();
			atak.pop_back();
		};
//		printf("**koniec rundy %d:%d **\n",ile,itsJednostki);

		//	std::list<uint16>::iterator iter;
		//	for(iter=atak.begin();iter!=atak.end();iter++)
		//		printf("%d ",*iter);
		//	printf("\n");
	};
	if(!itsJednostki)
	{
		itsOkupant=kogo;
		itsJednostki=ile;
//		Flaga();
	};
	return wynik;
};
void Planet::Flaga()
{
	if(itsJednostki)
	{
		if(itsOkupant&&itsGracz)
		{
			itsFlagaPoziom--;
			if(!itsFlagaPoziom)
				itsGracz=0;
			if(itsFlagaPoziom<0)
				itsFlagaPoziom=0;
		}
		else if((itsOkupant&&!itsGracz)||(!itsOkupant&&itsGracz))
		{
			itsFlagaPoziom++;
			if(itsFlagaPoziom==OCCUPY_MAX)
			{
				if(!itsGracz)
				{
					itsGracz=itsOkupant;
					itsOkupant=0;
				};
			};
			if(itsFlagaPoziom>OCCUPY_MAX)
				itsFlagaPoziom=OCCUPY_MAX;
		};
	};
};
void Planet::SetPlayer(uint16 gracz)
{
	itsGracz=gracz;
	itsFlagaPoziom=OCCUPY_MAX;
};
void Planet::EndTurn()
{
	Flaga();
	Jednostki();
};
void Planet::Jednostki()
{
	if(itsGracz&&!itsOkupant)
		itsJednostki++;
};
RETURNS::MOVE Planet::Zabierz(uint16 ile)
{
	if(ile<=itsJednostki)
	{
		itsJednostki-=ile;
		cout<<"zabierz ok"<<endl;
		return RETURNS::MOVE_OK;
	}
	cout<<"Zabierz za duzo"<<endl;
	return RETURNS::TOO_MUCH;
};
void Planet::Dodaj(uint16 ile)
{
	itsJednostki+=ile;
};
