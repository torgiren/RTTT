/*
 * sprite_sdl_2d.cpp
 *
 *  Created on: 24-12-2011
 *      Author: crm
 */

#include "sprite_sdl_2d.h"
#include "utils/resource.h"

bool SpriteSDL2D::loadGfx(const std::string& name)
	{
// Wczytywanie grafiki
	SDL_Surface *tmp;
	char *resGfx=Resource::load(name);
	if(resGfx==NULL)
		{
		printf("Sprite.loadGfx: Nie udalo sie wczytac grafiki \"%s\"\n", name.c_str());
		return 0;
		}
// Dekodowanie
	tmp=IMG_Load_RW(SDL_RWFromMem(resGfx, Resource::getLastSize()), 1);	// Ustawianie gfx do sprite
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

