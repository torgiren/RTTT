#include "windowengine.h"
#include "main.creammy.h"
#include "sprite.h"

const float SCREENFAR=1000;
const float SCREENNEAR=-1000;
const float DELTA_MIN=0.000001f;

namespace WindowEngine
	{
	bool initSDL();

	bool run=true;
	unsigned int flags=0x0;
	unsigned int frameTime=0;

	float delta=0.0f;

	set<void(*)(int)> keyDownHandles;
	set<void(*)(int)> keyUpHandles;
	set<void(*)(int)> keyPressedHandles;

	set<void(*)(int, int, int)> mouseDownHandles;
	set<void(*)(int, int, int)> mouseUpHandles;
	set<void(*)(int, int, int)> mouseMotionHandles;

	RenderType rt;
	WaitType wt;

	SDL_Event event;
	SDL_Surface *screen=NULL;

	Uint8 *keys=SDL_GetKeyState(NULL);
	}

/************************************************/
/****************** Funkcje rozne ***************/
/************************************************/
namespace WindowEngine
	{
	void setFlags(unsigned int sf)
		{
		flags=sf;
		}

	void setWaitType(WaitType swt)
		{
		wt=swt;
		}

	RenderType getRenderType()
		{
		return rt;
		}

	WaitType getWaitType()
		{
		return wt;
		}

	float getDelta()
		{
		return delta;
		}

	SDL_Surface* getScreen()
		{
		return (rt == SDL) ? screen : NULL;
		}
	}

/************************************************/
/****************** Funkcje glowne **************/
/************************************************/
namespace WindowEngine
	{
	bool init(RenderType srt, WaitType swt)
		{
		rt=srt;
		wt=swt;

		if(!initSDL())
			return false;
		return true;
		}

	bool initSDL()
		{
		static bool init=0;
		if(init == 0)
			{
			init=1;
			if(SDL_Init(SDL_INIT_VIDEO) < 0)
				{
				printf("WindowEngine.initSDL: Nie udalo sie zainicjowac sdl'a");
				return false;
				}
			//SDL_ShowCursor(SDL_DISABLE);
			SDL_WM_SetCaption(GAMENAME, NULL);
			}

		switch(rt)
			{
			case SDL:
				screen=SDL_SetVideoMode(SCREENWIDTH, SCREENHEIGHT, BPP, SDL_SWSURFACE | flags); //|((fullscreen)?SDL_FULLSCREEN:0));
				if(!screen)
					{
					printf("WindowEngine.initSDL: Nie udalo sie ustawic trybu video (SDL)");
					return false;
					}
			break;


			default:
				return false;
			break;
			}
		return true;
		}

	bool quit()
		{
		clearEventHandlers();
		SDL_Quit();
		return true;
		}

	bool update()
		{
		//if(SDL_GetTicks()-frameTime>6)
		//	printf("> %d\n", SDL_GetTicks()-frameTime);
		switch(wt)
			{
			case DELTA:
				delta=min(0.5f, (SDL_GetTicks() - frameTime) / 1000.0f);
				//delta=(SDL_GetTicks()-frameTime)/1000.0f;
				if(delta <= 0.0f)
					delta=DELTA_MIN;
			break;

			default:
			case DELAY:
				if(SDL_GetTicks() - frameTime < FPSDELAY - 1 && !keys[SDLK_LSHIFT])
					SDL_Delay(
							max(0, FPSDELAY - (int) (SDL_GetTicks() - frameTime)));
				delta=FPSDELAY / 1000.0f;
			break;
			}

		frameTime=SDL_GetTicks();

		while(SDL_PollEvent(&event))
			{
			switch(event.type)
				{
				case SDL_QUIT:
					run=0;
				break;

				case SDL_KEYDOWN:
					if(keys[SDLK_LALT])
						{
						if(event.key.keysym.sym == SDLK_RETURN)
							{
							if(flags & SDL_FULLSCREEN)
								flags=flags & (0xFFFFFFFF ^ SDL_FULLSCREEN);
							else
								flags|=SDL_FULLSCREEN;
							init(rt, wt);
							}
						else if(event.key.keysym.sym == SDLK_F4)
							run=0;
						}
					else if(event.key.keysym.sym == SDLK_F5)
						{
						init((rt == SDL) ? OPENGL : SDL, wt);
						Sprite::reload();
						}

					if(keyDownHandles.size()<1);
					else if(keyDownHandles.size()==1)
						(*keyDownHandles.begin())(event.key.keysym.sym);
					else
						for(set<void(*)(int)>::iterator it=keyDownHandles.begin(); it!=keyDownHandles.end(); ++it)
							(*it)(event.key.keysym.sym);
				break;

				case SDL_KEYUP:
					if(keyUpHandles.size()<1);
					else if(keyUpHandles.size()==1)
						(*keyUpHandles.begin())(event.key.keysym.sym);
					else
						for(set<void(*)(int)>::iterator it=keyUpHandles.begin(); it!=keyUpHandles.end(); ++it)
							(*it)(event.key.keysym.sym);
				break;

				case SDL_MOUSEBUTTONDOWN:
					if(mouseDownHandles.size()<1);
					else if(mouseDownHandles.size()==1)
						(*mouseDownHandles.begin())(event.button.x, event.button.y, event.button.button);
					else
						for(set<void(*)(int, int, int)>::iterator it=mouseDownHandles.begin(); it!=mouseDownHandles.end(); ++it)
							(*it)(event.button.x, event.button.y, event.button.button);
				break;

				case SDL_MOUSEBUTTONUP:
					if(mouseUpHandles.size()<1);
					else if(mouseUpHandles.size()==1)
						(*mouseUpHandles.begin())(event.button.x, event.button.y, event.button.button);
					else
						for(set<void(*)(int, int, int)>::iterator it=mouseUpHandles.begin(); it!=mouseUpHandles.end(); ++it)
							(*it)(event.button.x, event.button.y, event.button.button);
				break;

				case SDL_MOUSEMOTION:
					if(mouseMotionHandles.size()<1);
					else if(mouseMotionHandles.size()==1)
						(*mouseMotionHandles.begin())(event.button.x, event.button.y, event.button.button);
					else
						for(set<void(*)(int, int, int)>::iterator it=mouseMotionHandles.begin(); it!=mouseMotionHandles.end(); ++it)
							(*it)(event.button.x, event.button.y, event.button.button);
				break;

				default:
				break;
				}
			}

		return run;
		}

	bool print()
		{
		switch(rt)
			{
			default:
			case SDL:
				if(!screen)
					break;

				SDL_Flip(screen);

				SDL_Rect r;
				r.x=0;
				r.y=0;
				r.w=SCREENWIDTH;
				r.h=SCREENHEIGHT;
				SDL_FillRect(screen, &r, 0x0088FF);
			break;
			}

		return true;
		}
	}

/************************************************/
/****************** Handlery ********************/
/************************************************/
namespace WindowEngine
	{
	/***** Dodawanie *****/
	bool addKeyDownEventHandler(void(*handle)(int))
		{
		return keyDownHandles.insert(handle).second;
		}

	bool addKeyUpEventHandler(void(*handle)(int))
		{
		return keyUpHandles.insert(handle).second;
		}

	bool addKeyPressedEventHandler(void(*handle)(int))
		{
		return keyPressedHandles.insert(handle).second;
		}

	bool addMouseDownEventHandler(void(*handle)(int, int, int))
		{
		return mouseDownHandles.insert(handle).second;
		}

	bool addMouseUpEventHandler(void(*handle)(int, int, int))
		{
		return mouseUpHandles.insert(handle).second;
		}

	bool addMouseMotionEventHandler(void(*handle)(int, int, int))
		{
		return mouseMotionHandles.insert(handle).second;
		}

	/***** Kasowanie *****/
	void delKeyDownEventHandler(void(*handle)(int))
		{
		keyDownHandles.erase(handle);
		}

	void delKeyUpEventHandler(void(*handle)(int))
		{
		keyUpHandles.erase(handle);
		}

	void delKeyPressedEventHandler(void(*handle)(int))
		{
		keyPressedHandles.erase(handle);
		}

	void delMouseDownEventHandler(void(*handle)(int, int, int))
		{
		mouseDownHandles.erase(handle);
		}

	void delMouseUpEventHandler(void(*handle)(int, int, int))
		{
		mouseUpHandles.erase(handle);
		}

	void delMouseMotionEventHandler(void(*handle)(int, int, int))
		{
		mouseMotionHandles.erase(handle);
		}

	void clearEventHandlers()
		{
		keyDownHandles.clear();
		keyUpHandles.clear();
		keyPressedHandles.clear();

		mouseDownHandles.clear();
		mouseUpHandles.clear();
		mouseMotionHandles.clear();
		}

	bool getKeyState(int key)
		{
		return keys[key];
		}

	bool getMouseState(int key)
		{
		return SDL_GetMouseState(NULL, NULL)&key;
		}
	}
