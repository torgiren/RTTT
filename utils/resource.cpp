/*
 * resource.cpp
 *
 *  Created on: 23-12-2011
 *      Author: crm
 */

#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <set>

#include "resource.h"
#include "resfile.h"
#include "listdir.h"
#include "log.h"

namespace Resource
	{
	unsigned int size=0u;

	std::map<std::string, Resfile *> resfiles;	// Lista obslugiwanych resfile
	std::set<std::string> raw;					// Pliki, ktore nie sa w zadnym resfile (odczytywane z prosto dysku)

	void clearCache() {raw.clear();};

	char* readRes(const std::string& file);
	char* readRaw(const std::string& file);

	int readResSize(const std::string& file);
	int readRawSize(const std::string& file);
	}

void Resource::init(const std::string& name)
	{
	//clear();

	std::vector<std::string> files;
	if(listDir(name, files)<1)
		{
		Log::fail("Resource.init: Nie znaleziono folderu \"%s\" lub jest on pusty", name.c_str());
		return;
		}

	for(unsigned int i=2; i<files.size(); ++i)
		{
		try
			{
			Resfile *r=new Resfile();
			if(!r->open(name+files[i]))
				{
				delete r;
				continue;
				}
			resfiles[files[i]]=r;
			}
		catch(std::bad_alloc&)
			{
			Log::fail("Resource.init: Nie udalo sie stworzyc resfile pliku \"%s\"", files[i].c_str());
			}
		}
	}

void Resource::clear()
	{
	Log::info("Resource.clear: Czyszczenie");
	for(std::map<std::string, Resfile *>::iterator it=resfiles.begin(); it!=resfiles.end(); ++it)
		delete it->second;
	resfiles.clear();
	raw.clear();
	Log::ok("Resource.clear: Wyczyszczono");
	}

char* Resource::load(const std::string& file)
	{
	size=0u;
	if(raw.find(file)!=raw.end())
		return readRaw(file);
	else
		return readRes(file);
	}

char* Resource::readRes(const std::string& file)
	{
	for(std::map<std::string, Resfile *>::iterator it=resfiles.begin(); it!=resfiles.end(); ++it)
		{
		Resfile *res=it->second;
		if(res->checkFile(file))
			{
			size=res->getSize(file);
			//return res->load(it->first+":"+file);
			return res->load(file);
			}
		}
	return readRaw(file);
	}

char* Resource::readRaw(const std::string& file)
	{
	std::fstream in(file.c_str(), std::ios::binary|std::ios::in);
	if(!in)
		{
		Log::fail("resource.readRaw: Nie udalo sie otworzyc pliku \"%s\"", file.c_str());
		return NULL;
		}
	char *tmp;
	in.seekg(0, std::ios::end);
	size=in.tellg();
	in.seekg(0, std::ios::beg);

	try
		{
		tmp=new char[size+1];
		}
	catch(std::bad_alloc&)
		{
		Log::fail("resource.readRaw: Nie udalo sie zajac miejsca na plik \"%s\"", file.c_str());
		return NULL;
		}

	in.read(tmp, size);
	tmp[size]='\0';

	if(raw.insert(file).second)
		Log::ok("resource.readRaw: Wczytano plik \"%s\"", file.c_str());
	return tmp;
	}

int Resource::getSize(const std::string& file)
	{
	size=0u;
	if(raw.find(file)!=raw.end())
		return readRawSize(file);
	else
		return readResSize(file);
	}

int Resource::readResSize(const std::string& file)
	{
	for(std::map<std::string, Resfile *>::iterator it=resfiles.begin(); it!=resfiles.end(); ++it)
		{
		Resfile *res=it->second;
		if(res->checkFile(file))
			{
			size=res->getSize();
			return res->getSize(file);
			}
		}
	return readRawSize(file);
	}

int Resource::readRawSize(const std::string& file)
	{
	std::fstream in(file.c_str(), std::ios::binary|std::ios::in);
	if(!in)
		{
		Log::fail("resource.readRaw: Nie udalo sie otworzyc pliku");
		return 0;
		}
	in.seekg(0, std::ios::end);
	size=in.tellg();
	return in.tellg();
	}

int Resource::getLastSize()
	{
	return size;
	}
