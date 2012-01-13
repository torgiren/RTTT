#ifndef ENGINE_H
#define ENGINE_H

struct SDL_Surface;

namespace Engine
	{
	enum RenderType {SDL, OPENGL};
	enum WaitType {DELAY, DELTA};

	bool init(RenderType rt=SDL, WaitType=DELAY);			// Inicjuje wszystko co potrzebne
	bool update();
	bool print();
	bool quit();											// Kasuje wszystko co zbedne

	void setFlags(unsigned int flags);
	void setWaitType(WaitType wt);

	RenderType getRenderType();
	WaitType getWaitType();
	float getDelta();

	bool addKeyDownEventHandler(void (*handle)(int));
	bool addKeyUpEventHandler(void (*handle)(int));
	bool addKeyPressedEventHandler(void (*handle)(int));

	bool addMouseDownEventHandler(void (*handle)(int, int, int));
	bool addMouseUpEventHandler(void (*handle)(int, int, int));
	bool addMouseMotionEventHandler(void (*handle)(int, int, int));

	void delKeyDownEventHandler(void (*handle)(int));
	void delKeyUpEventHandler(void (*handle)(int));
	void delKeyPressedEventHandler(void (*handle)(int));

	void delMouseDownEventHandler(void (*handle)(int, int, int));
	void delMouseUpEventHandler(void (*handle)(int, int, int));
	void delMouseMotionEventHandler(void (*handle)(int, int, int));

	void clearEventHandlers();

	bool getKeyState(int key);
	bool getMouseState(int key);

	SDL_Surface* getScreen();

	//bool setScreen(int w, int h, int bpp, int fullscreen);	// Tworzy okienko
	}

#endif // ENGINE_H
