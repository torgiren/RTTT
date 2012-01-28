#include <iostream>
#include <string>
#include <cstdio>
#include "gameengine.h"
using namespace std;
int main(int argc, char* argv[])
{
	cout<<"Witaj poruczniku...\nPlanujesz swoją własną bitwę czy dołączyć się do innej?\n";
menu:
	cout<<"1) Własna bitwa\n";
	cout<<"2) Przyłączenie sie do istniejącej"<<endl;
	char opt;
	scanf("%c",&opt);
	bool server=false;
	switch(opt)
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
	if(server)
	{
		int size,graczy;
		cout<<"Na jakim dużym obszarze będzie prowadzona bitwa?"<<endl;
		cin>>size;
		cout<<"Na ilu przewidujesz przeciwników?"<<endl;	
		cin>>graczy;
		cout<<"Tak jest... Przygotowuję odpowiedni obszar..."<<endl;
		GameEngine silnik(size,graczy);
	}
	else
	{
		cout<<"Proszę wprowadzić cztery współrzędne bitwy (xxx.xxx.xxx.xxx):"<<endl;
		string ip;
		cin>>ip;
	};
	return 0;
};
