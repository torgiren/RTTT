/*
 * Screen.cpp
 *
 *  Created on: 12-01-2012
 *      Author: crm
 */

#include "screen.h"
#include "drawing.h"

const int CUBE_SIZE=64;
const int CUBE_DIST=32; //CUBE_SIZE*6;

inline void sincos(float ang, float& s, float& c)
	{
	asm	(
		"fsincos\n\t"
		: "=t" (c), "=u" (s)
		: "0" (ang)
		);
	}

struct Cube
	{
	Cube(int x=0, int y=0, int z=0):
		x(x), y(y), z(z)
		{
		reset();
		}

	void reset()
		{
	// Przod
		verts[ 0]=Vertex(0, 0, 0);
		verts[ 1]=Vertex(1, 0, 0);
		verts[ 2]=Vertex(1, 1, 0);
		verts[ 3]=Vertex(0, 1, 0);
	// Tyl
		verts[ 4]=Vertex(0, 0, 1);
		verts[ 5]=Vertex(1, 0, 1);
		verts[ 6]=Vertex(1, 1, 1);
		verts[ 7]=Vertex(0, 1, 1);
	// Tyl
		verts[ 4]=Vertex(0, 0, 1);
		verts[ 5]=Vertex(1, 0, 1);
		verts[ 6]=Vertex(1, 1, 1);
		verts[ 7]=Vertex(0, 1, 1);


		for(int i=0; i<VERT_COUNT; ++i)
			verts[i]=verts[i]*CUBE_SIZE+Vertex(x, y, z)*(CUBE_SIZE+CUBE_DIST);
		}

	static const int VERT_COUNT=24;

	int x, y, z;
	unsigned int col;

	Vertex verts[VERT_COUNT];
	};

/************************************************/
/****************** Funkcje *********************/
/************************************************/
namespace Screen
	{
	void drawCube(Cube c);

	void mdown(int x, int y, int key);
	void mup(int x, int y, int key);
	void mmove(int x, int y, int key);
	void mroll(bool down);
	}

/************************************************/
/****************** Zmienne *********************/
/************************************************/
namespace Screen
	{
	bool lmb=false;		// Wcisniety lewy przycisk myszy
	bool rmb=false;		// Wcisniety prawy przycisk myszy
	bool mmb=false;		// Wcisnieta rolka

	int lx=-1;			// Ostatni x myszy
	int ly=-1;			// Ostatni y myszy
	int mx=0;			// Ostatni ruch w x
	int my=0;			// Ostatni ruch w y

	float rx=	0.0f;	// Aktualny obrot w x
	float ry=	0.0f;	// Aktualny obrot w y
	float rz=	0.0f;	// Aktualny obrot w z
	float scale=0.0f;	// Aktualna skala

	const float FRICTION=0.5f;	// Tarcie, zwalnia obrot
	float spdx=	0.0f;	// Szybkosc obrotu w x
	float spdy= 0.0f;	// Szybkosc obrotu w y

	int size=4;
	vector<vector<vector<Cube> > > area;
	}

/************************************************/
/****************** Funkcje glowne **************/
/************************************************/
namespace Screen
	{
	void init()
		{
		WindowEngine::delMouseDownEventHandler		(mdown);
		WindowEngine::delMouseUpEventHandler		(mup);
		WindowEngine::delMouseMotionEventHandler	(mmove);

		WindowEngine::addMouseDownEventHandler		(mdown);
		WindowEngine::addMouseUpEventHandler		(mup);
		WindowEngine::addMouseMotionEventHandler	(mmove);

		setSize(4);
		}

	void update()
		{
		//
		}

	void draw()
		{
		Drawing::clearZBuff();

		for(int x=0; x<size; ++x)
			{
			for(int y=0; y<size; ++y)
				{
				for(int z=0; z<size; ++z)
					{
					//area[x][y][z].reset();
					//drawCube(area[x][y][z]);
					}
				}
			}
		}

	void setSize(int ss)
		{
		size=ss;

		area.resize(size);
		for(int x=0; x<size; ++x)
			{
			area[x].resize(size);
			for(int y=0; y<size; ++y)
				{
				area[x][y].resize(size);
				for(int z=0; z<size; ++z)
					{
					area[x][y][z]=Cube(x, y, z);
					area[x][y][z].col=rand();
					}
				}
			}
		}
	}

/************************************************/
/****************** Obsluga myszy ***************/
/************************************************/
namespace Screen
	{
	void mdown(int x, int y, int key)
		{
		if(key==SDL_BUTTON_LEFT)
			lmb=true;
		else if(key==SDL_BUTTON_MIDDLE)
			mmb=true;
		else if(key==SDL_BUTTON_RIGHT)
			rmb=true;
		else if(key==SDL_BUTTON_WHEELUP || key==SDL_BUTTON_WHEELDOWN)
			mroll(key==SDL_BUTTON_WHEELDOWN);

		if(lmb)
			{
			lx=x;
			ly=y;
			}
		}

	void mup(int x, int y, int key)
		{
		if(key==SDL_BUTTON_LEFT)
			lmb=false;
		else if(key==SDL_BUTTON_MIDDLE)
			mmb=false;
		else if(key==SDL_BUTTON_RIGHT)
			rmb=false;
		}

	void mmove(int x, int y, int key)
		{
		if(!lmb)
			return;

		mx=-(y-ly);
		my= (x-lx);

		lx=x;
		ly=y;
		}

	void mroll(bool down)
		{
		//
		}
	}
