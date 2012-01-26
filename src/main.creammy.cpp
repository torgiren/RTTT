#include "main.creammy.h"
#include "sprite.h"
#include "text.h"
#include "drawing.h"
#include "screen.h"

#undef main
int main(int , char *[])
	{
	printf("Start");
	printf("Build: %s %s", __DATE__, __TIME__);

	srand(time(NULL));

	if(!WindowEngine::init(WindowEngine::SDL, WindowEngine::DELTA))
		{
		printf("Nie udalo sie stworzyc okienka\n");
		return 100;
		}
	Drawing::setSurface(WindowEngine::getScreen());
	Screen::init();
	Screen::setSize(4);

	Text info(0, 32, 32, 0, 0, 0, Sprite::load("data/font_00"), "Pierwszy widoczny tekst, wooo~", SCREENWIDTH-64, SCREENHEIGHT-64);

	unsigned int fpsfr=0, fpsft=SDL_GetTicks();
	while(WindowEngine::update())
		{
		fpsfr++;
		if(fpsft+1000<SDL_GetTicks())
			{
			printf("fps: %0.2f (%d/%d)", (fpsfr*1000.0)/(SDL_GetTicks()-fpsft), fpsfr, SDL_GetTicks()-fpsft);
			fpsfr=0;
			fpsft=SDL_GetTicks();
			}

		/*Drawing::setColor(0xFFFF0000);
		Drawing::drawLine(Vertex(96, 96, 96), Vertex(128, 128, 128));
		Drawing::drawLine(Vertex(160, 68, 128), Vertex(160, 100, 128));
		Drawing::drawLine(Vertex(212, 192, 128), Vertex(180, 160, 128));

		Drawing::drawLine(Vertex(340, 285, 24), Vertex(365, 435, 69));

		Drawing::setColor(0xFF00FF00);
		Drawing::drawTriangle(Vertex(128, 128, 128), Vertex(160, 100, 128), Vertex(180, 160, 128));
		Drawing::drawTriangle(Vertex(280, 260, 228), Vertex(260, 200, 228), Vertex(228, 228, 228));*/

		//Drawing::setColor(0xFF0000FF);
		//Drawing::drawQuad(Vertex(24, 200, 32), Vertex(8, 216, 32), Vertex(24, 232, 32), Vertex(40, 216, 32));
		//Drawing::drawQuad(Vertex(300, 305, 32), Vertex(315, 420, 64), Vertex(405, 415, 64), Vertex(410, 320, 32));
		//Drawing::drawQuad(Vertex(32, 32, 64), Vertex(35, 68, 32), Vertex(72, 76, 32), Vertex(74, 30, 64));

		Screen::update();
		Screen::draw();

		info.print();

		WindowEngine::print();
		}

	Sprite::clear();
	WindowEngine::quit();
	printf("Stop");
	return 0;
	}

