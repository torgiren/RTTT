/*
 * sprite_sdl_2d.cpp
 *
 *  Created on: 24-12-2011
 *      Author: crm
 */

#include "sprite_sdl_2d.h"

bool SpriteSDL2D::loadGfx(const std::string& name)
	{
// Wczytywanie grafiki
	fstream in;
	SDL_Surface *tmp=NULL;

	char *resGfx=NULL;
	unsigned int size=0;

	in.open(name.c_str(), ios::binary|ios::in);

	if(!in.is_open())
		{
		printf("Sprite.loadGfx: Nie udalo sie wczytac grafiki (plik nie moze byc otwarty) \"%s\"\n", name.c_str());
		return 0;
		}

	in.seekg(0, ios::end);
	size=in.tellg();
	in.seekg(0, ios::beg);

	if(size<=0)
		{
		printf("Sprite.loadGfx: Nie udalo sie wczytac grafiki (plik pusty) \"%s\"\n", name.c_str());
		return 0;
		}

	try
		{
		resGfx=new char[size];
		}
	catch(bad_alloc&)
		{
		printf("Sprite.loadGfx: Nie udalo się zajac miejsca na obrazek \"%s\"\n", name.c_str());
		return 0;
		}
	in.read(resGfx, size);
	in.close();

// Dekodowanie
	tmp=IMG_Load_RW(SDL_RWFromMem(resGfx, size), 1);	// Ustawianie gfx do sprite
	delete [] resGfx;
	if(tmp==NULL)
		{
		printf("Sprite.loadGfx: Nie udalo sie zdekompresowac grafiki \"%s\"\n", name.c_str());
		return 0;
		}
// Zmiana formatu
	sprite=SDL_DisplayFormatAlpha(tmp);
	SDL_FreeSurface(tmp);
	if(sprite==NULL)
		{
		printf("Sprite.loadGfx: Nie udalo sie przekonwertowac grafiki\n");
		return 0;
		}
// Generowanie maski
	if(!loadMask(sprite->pixels, sprite->w, sprite->h, sprite->format->BitsPerPixel))
		{
		printf("Sprite.loadGfx: Nie udalo sie wygenerowac maski kolizji\n");
		SDL_FreeSurface(sprite);
		return 0;
		}
	return 1;
	}

void SpriteSDL2D::print(float x, float y, float , int anim, int frame, unsigned char , float px, float py, unsigned char , unsigned char , unsigned char )
	{
	const Anim::AnimFrame& frm=anims[anim].getFrame(frame);

	//x-=Screen::getPosX();
	//y-=Screen::getPosY();
	//if(px!=1.0f)
	//	x+=Screen::getPosX()*(1-px);
	//if(py!=1.0f)
	//	y+=Screen::getPosY()*(1-py);

	SDL_Rect offset, clip;
	offset.x=x-frm.spotx; offset.y=y-frm.spoty; offset.w=frm.w; offset.w=frm.h;
	clip.x=frm.x; clip.y=frm.y; clip.w=frm.w; clip.h=frm.h;
	SDL_BlitSurface(sprite, &clip, WindowEngine::getScreen(), &offset);
	}

