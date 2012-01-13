#include "main.creammy.h"
#include "sprite.h"
#include "utils/resource.h"
#include "drawing.h"
#include "game.h"

#undef main
int main(int , char *[])
	{
	printf("Start");
	printf("Build: %s %s", __DATE__, __TIME__);

	srand(time(NULL));

	if(!Engine::init(Engine::SDL, Engine::DELAY))
		{
		printf("Nie udalo sie stworzyc okienka\n");
		return 100;
		}
	Drawing::setSurface(Engine::getScreen());
	Resource::init(RESLIST);
	Game::init();

	unsigned int fpsfr=0, fpsft=SDL_GetTicks();
	while(Engine::update())
		{
		fpsfr++;
		if(fpsft+1000<SDL_GetTicks())
			{
			printf("fps: %0.2f (%d/%d)", (fpsfr*1000.0)/(SDL_GetTicks()-fpsft), fpsfr, SDL_GetTicks()-fpsft);
			fpsfr=0;
			fpsft=SDL_GetTicks();
			}

		Drawing::setColor(0x80808080);
		Drawing::drawLineShr(0, 0, SCREENWIDTH, SCREENHEIGHT);
		Drawing::drawLineShr(0, SCREENHEIGHT/2, SCREENWIDTH, SCREENHEIGHT/2);
		Drawing::drawLineShr(0, SCREENHEIGHT, SCREENWIDTH*3/4, 0);
		Drawing::drawLineShr(SCREENWIDTH/2, 0, SCREENWIDTH/2, SCREENHEIGHT);
		Drawing::drawLineShr(SCREENWIDTH*3/4, 0, SCREENWIDTH, SCREENHEIGHT);

		Drawing::setColor(0xFFFFFFFF);
		Game::update();
		Game::draw();

		Engine::print();
		}

	Sprite::clear();
	Engine::quit();
	printf("Stop");
	return 0;
	}

