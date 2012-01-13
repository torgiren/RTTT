#ifndef SPRITE_SDL_2D_H
#define SPRITE_SDL_2D_H

#include "sprite.h"
#include "main.creammy.h"

class SpriteSDL2D: public Sprite
	{
	private:
		bool loadGfx(const std::string& name);

		SDL_Surface *sprite;
	public:
		SpriteSDL2D(const std::string& name="", int w=0, int h=0): Sprite(name, w, h), sprite(NULL) {}
		virtual ~SpriteSDL2D() {if(sprite) SDL_FreeSurface(sprite);}

		void print(float x, float y, float z, int anim, int frame, unsigned char alpha=255u, float px=1.0f, float py=1.0f, unsigned char r=255u, unsigned char g=255u, unsigned char b=255u);
		inline void flush() {};
	};

#endif // SPRITE_SDL_2D_H
