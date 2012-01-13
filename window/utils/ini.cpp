/*
 * Ini.cpp
 *
 *  Created on: 18-10-2011
 *      Author: crm
 */

#include <fstream>

#include "Ini.h"

using namespace std;

bool Ini::open(const string& fileName, const string& group)
	{
	//printf("> %s - %s\n", fileName.c_str(), group.c_str());
	fstream in(fileName.c_str(), ios::in );
	if(!in.is_open())
		return false;
	clear();		// Przeniesione na poczatek funkcji celem unikniecia zapetlenia npc

	bool read=false;
	char tmp[1025];
	while(in)
		{
		in.getline(tmp, 1024);
		tmp[1024]='\0';
		if(tmp[0]==';')
			continue;
		if(!read)
			{
			if(tmp[0]=='[')
				{
				int len;
				for(len=1; len<1024; ++len)
					{
					if(tmp[len]==']')
						break;
					}
				if(group.compare(0, group.length(), tmp+1, len-1)==0)
					read=1;
				}
			}
		else
			{
			if(tmp[0]=='[')
				break;
			int eqpos;		// pozycja '='
			for(eqpos=1; eqpos<1024; ++eqpos)
				{
				if(tmp[eqpos]=='=')
					break;
				}
			string str=tmp;
			if(eqpos>=1024 || str.length()<1)
				continue;

			vals[str.substr(0, eqpos)]=str.substr(eqpos+1, str.length()-eqpos-1);
			}
		}

	return true;
	}

void Ini::clear()
	{
	vals.clear();
	}

void Ini::get(const string& key, string& val)
	{
	val=vals[key];
	}

string& Ini::get(const string& key)
	{
	return vals[key];
	}
