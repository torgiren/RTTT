#include "main.creammy.h"
#include "sprite.h"
#include "sprite_sdl_2d.h"
#include "utils/resource.h"
#include "utils/parser.h"

void Sprite::SpritePtr::animate()
	{
	if(!sprite)
		return;
	sprite->animate(anim, frame, spd);
	}

void Sprite::SpritePtr::print(float x, float y, float z, unsigned char alpha, float px, float py, unsigned char r, unsigned char g, unsigned char b)
	{
	if(sprite)
		sprite->print(x, y, z, anim, frame, alpha, px, py, r, g, b);
	}

std::map<std::string, Sprite *> Sprite::sprites;

Sprite::Sprite(const std::string& sname, int w, int h):
	name(sname), w(w), h(h), mask(NULL)
	{
	//
	}

Sprite::~Sprite()
	{
	setSpritePtrs(NULL);
	spritePtrs.clear();
	}

void Sprite::setSpritePtrs(Sprite *s)
	{
	if(s==this)
		return;
	//for(std::set<SpritePtr *>::iterator it=spritePtrs.begin(); it!=spritePtrs.end(); ++it)
	while(spritePtrs.size()>0)
		(*spritePtrs.begin())->setSprite(s);
	}


void Sprite::print()
	{
	for(std::map<std::string, Sprite *>::iterator it=sprites.begin(); it!=sprites.end(); ++it)
		it->second->flush();
	}

void Sprite::clear()
	{
	printf("Sprite.clear: Czyszczenie");
	for(std::map<std::string, Sprite *>::iterator it=sprites.begin(); it!=sprites.end(); ++it)
		delete it->second;
	sprites.clear();
	printf("Sprite.clear: Wyczyszczono");
	}

void Sprite::reload()
	{
	for(std::map<std::string, Sprite *>::iterator it=sprites.begin(); it!=sprites.end(); ++it)
		{
		Sprite *sprite=it->second;
		Sprite *newSprite=load(sprite->getName(), true);
		sprite->setSpritePtrs(newSprite);
		delete sprite;
		}
	}


Sprite* Sprite::load(const std::string& name, bool force)
	{
	if(!force && sprites.find(name)!=sprites.end())
		return sprites[name];
/**** Sprawdzanie typu obrazka ****/
	Sprite *spr;

	//std::string name3d=name+MDLEXT;
	std::string nameimg=name+IMGEXT;
	std::string nameani=name+ANIMEXT;

	try
		{
		if(Engine::getRenderType()==Engine::SDL)
			spr=new SpriteSDL2D(name);
		}
	catch(std::bad_alloc&)
		{
		printf("Nie udalo sie stworzyc sprite \"%s\" (bad alloc)", name.c_str());
		return NULL;
		}

	if(!spr->loadGfx(nameimg))
		{
		printf("Nie udalo sie wczytac obrazka \"%s\"", nameimg.c_str());
		delete spr;
		return NULL;
		}

	if(!spr->loadAnims(nameani))
		{
		printf("Nie udalo sie wczytac animacji \"%s\"", nameani.c_str());
		delete spr;
		return NULL;
		}

	sprites[name]=spr;

	return spr;
	}

bool Sprite::loadMask(void *vpixs, int w, int h, int bpp)	// bpp ignorowane, tylko 32 (alfa 0 -> maska 0)
	{
	int *pixs=reinterpret_cast<int *>(vpixs);
	int size=w*h;

	try
		{
		mask=new bool[w*h];
		memset(mask, 1, w*h);
		}
	catch(std::bad_alloc&)
		{
		printf("Nie udalo sie zajac miejsca na maske kolizji");
		return false;
		}

	if(bpp!=32)
		{
		printf("BPP powinno wynosic 32, maska nie wygenerowana");
		return true;
		}

	for(int i=0; i<size; ++i)
		{
		if((pixs[i]&0xFF000000)<32)
			mask[i]=0;
		}
	return true;
	}

bool Sprite::loadAnims(const string& name)
	{
	if(name.length()<2)
		return 0;
	//printf("> \"%s\"\n", name);
	map<string, int> animNamesTmp;
	Parser parsLine;
	Parser parsSpace;
	parsLine.setDelimiter("\n\r");
	parsSpace.setDelimiter(" \t");

	anims.clear();
	animNames.clear();

	char *tmp=Resource::load(name);
	if(tmp==NULL)
		{
		printf("Sprite2D.loadAnims: Nie znaleziono informacji o animacjach, uzywanie calego obrazka");
		anims.push_back(Anim(0.0f, 0.0f));
		anims.back().addFrame(0, 0, w, h, 0, 0, 0, 0);
		return 1;
		}

	parsLine=tmp;
	delete [] tmp;
	for(int i=0; i<parsLine.count(); i++)
		{
		parsSpace=parsLine[i];
		//printf("> %s\n", parsSpace.getText().c_str());
		if(parsSpace.count()<1)
			continue;
		else if(parsSpace[0]=="--")
			continue;
		else if(parsSpace[0]=="anim")
			{
			if(parsSpace.count()<2)	// Wstawianie poklatkowe
				{
				printf("Sprite2D.loadAnim: Brak wymaganych informacji (\"%s\")", parsSpace.getText().c_str());
				break;
				}
			anims.push_back(Anim(parsSpace.valFloat(1), 0));
			if(parsSpace.count()>2)
				{
				anims.back().setFret(parsSpace.val(2));
				if(parsSpace.count()>3)
					animNamesTmp[parsSpace[3]]=i;
				}
			}
		else if(parsSpace[0]=="frame")
			{
			Anim& a=anims.back();
			int count=parsSpace.val(1);
			if(count<=0)
				a.addFrame(0, 0, 0, 0);
			//printf("> Klatek: %d\n", count);
			for(int i=0; i<count; i++)
				{
				if(parsSpace.count()<4)
					a.addFrame(0, 0, 0, 0);
				else if(parsSpace.count()<8)
					a.addFrame(parsSpace.val(2)+parsSpace.val(4)*i, parsSpace.val(3), parsSpace.val(4), parsSpace.val(5));
				else if(parsSpace.count()<10)
					a.addFrame(parsSpace.val(2)+parsSpace.val(4)*i, parsSpace.val(3), parsSpace.val(4), parsSpace.val(5), parsSpace.val(6), parsSpace.val(7));
				else if(parsSpace.count()<14)
					a.addFrame(parsSpace.val(2)+parsSpace.val(4)*i, parsSpace.val(3), parsSpace.val(4), parsSpace.val(5), parsSpace.val(6), parsSpace.val(7), parsSpace.val(8), parsSpace.val(9));
				else
					a.addFrame(parsSpace.val(2)+parsSpace.val(4)*i, parsSpace.val(3), parsSpace.val(4), parsSpace.val(5), parsSpace.val(6), parsSpace.val(7), parsSpace.val(8), parsSpace.val(9), parsSpace.val(10), parsSpace.val(11), parsSpace.val(12), parsSpace.val(13));
				}
			}
		//else if(parsSpace[0]=="anim")
		else if(parsSpace.isVal(0) && parsSpace.count()>6)			// Animacje 'na szybko'	// Proste zalozenie, jesli pierwsza wartosc jest liczba to dodawana jest animacja
			{
			// 5 0 24 12 24 7 24
			if(parsSpace.count()<7)
				{
				printf("Sprite2D.loadAnims: Brak wymaganych informacji (\"%s\")\n", parsSpace.getText().c_str());
				break;
				}
			anims.push_back(Anim(0.0f, 0));
			Anim& a=anims.back();
			int count=parsSpace.val(0);
			for(int i=0; i<count; ++i)
				a.addFrame(parsSpace.val(1)+parsSpace.val(3)*i, parsSpace.val(2), parsSpace.val(3), parsSpace.val(4), parsSpace.val(5), parsSpace.val(6));
			if(parsSpace.count()>7)
				{
				a.setAspd(parsSpace.valFloat(7));
				if(parsSpace.count()>8)
					a.setFret(parsSpace.val(8));
				}
			}
		}
// Dodawanie nazw do mapy
	//int i=0;
	for(map<string, int>::iterator it=animNamesTmp.begin(); it!=animNamesTmp.end(); ++it)
		{
		animNames[it->first]=&anims[it->second];
		//printf("Sprite2d.loadAnims: Dodawanie nazwy, animacja %d, nazwa %s", i++, it->first.c_str());
		}
// Sprawdz czy wczytala sie przynajmniej jedna animacja
	if(anims.size()<1)
		return 0;
// Sprawdzanie czy wszystkie animacje maja conajmniej jedna klatke
	for(unsigned int i=0; i<anims.size(); i++)
		if(anims[i].getFrameCount()<1)
			anims[i].addFrame(0, 0, 0, 0);
	//printf("INFO: Sprite.loadAnim: Ilosc animacji: %d\n", anims.size());
	return 1;
	}

void Sprite::animate(int anim, float& frame, float spd)
	{
	Anim& a=getAnim(anim);
	if(spd<0.0f)
		frame+=a.getAspd()*Engine::getDelta();
	else
		frame+=spd*Engine::getDelta();
	if((int)frame>=a.getFrameCount())
		{
		float diff=frame-(int)(frame);
		frame=a.getFret()+diff;
		}
	}
