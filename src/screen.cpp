/*
 * Screen.cpp
 *
 *  Created on: 12-01-2012
 *      Author: crm
 */

#include "screen.h"
#include "drawing.h"

inline void sincos(float ang, float& s, float& c)
	{
	asm	(
		"fsincos\n\t"
		: "=t" (c), "=u" (s)
		: "0" (ang)
		);
	}

/************************************************/
/****************** Funkcje *********************/
/************************************************/
namespace Screen
	{
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

	float rx=	0.0f;	// Aktualny obrot w x
	float ry=	0.0f;	// Aktualny obrot w y
	float rz=	0.0f;	// Aktualny obrot w z
	float scale=0.0f;	// Aktualna skala

	const float FRICTION=0.5f;	// Tarcie, zwalnia obrot
	float spdx=	0.0f;	// Szybkosc obrotu w x
	float spdy= 0.0f;	// Szybkosc obrotu w y

	int size;
	vector<vector<vector<int> > > area;
	}

struct Vertex
	{
	Vertex(float x, float y, float z):
		x(x), y(y), z(z) {};

	Vertex& operator=(const Vertex& v)
		{
		x=v.x;
		y=v.y;
		z=v.z;
		return *this;
		}

	Vertex operator+(const Vertex& v)
		{
		return Vertex(x+v.x, y+v.y, z+v.z);
		}

	Vertex operator-(const Vertex& v)
		{
		return Vertex(x-v.x, y-v.y, z-v.z);
		}

	Vertex operator*(float v)
		{
		return Vertex(x*v, y*v, z*v);
		}

	Vertex operator/(float v)
		{
		return Vertex(x/v, y/v, z/v);
		}

	float x, y, z;
	};

/************************************************/
/****************** Funkcje glowne **************/
/************************************************/
namespace Screen
	{
	void init()
		{
		WindowEngine::addMouseDownEventHandler		(mdown);
		WindowEngine::addMouseUpEventHandler		(mup);
		WindowEngine::addMouseMotionEventHandler	(mmove);
		}

	void update()
		{
		//
		}

	void draw()
		{
		Vertex verts[]={
			// Przod
				Vertex(0, 0, 0),
				Vertex(0, 1, 0),

				Vertex(0, 1, 0),
				Vertex(1, 1, 0),

				Vertex(1, 1, 0),
				Vertex(1, 0, 0),

				Vertex(1, 0, 0),
				Vertex(0, 0, 0),
			// Tyl
				Vertex(0, 0, 1),
				Vertex(0, 1, 1),

				Vertex(0, 1, 1),
				Vertex(1, 1, 1),

				Vertex(1, 1, 1),
				Vertex(1, 0, 1),

				Vertex(1, 0, 1),
				Vertex(0, 0, 1),
			// Lewo
				Vertex(0, 0, 0),
				Vertex(0, 0, 1),

				Vertex(1, 0, 0),
				Vertex(1, 0, 1),
			// Prawo
				Vertex(0, 1, 0),
				Vertex(0, 1, 1),

				Vertex(1, 1, 0),
				Vertex(1, 1, 1)
				};

		Vertex tl(SCREENWIDTH/2-75, SCREENHEIGHT/2-75, 0);

		//rx=30;
		//ry++;

		float sinrx, cosrx;
		float sinry, cosry;

		sincos(rx*DEGTORAD, sinrx, cosrx);
		sincos(ry*DEGTORAD, sinry, cosry);

		//lrx=rx;
		//lry=ry;

		for(unsigned int i=0; i<sizeof(verts)/sizeof(Vertex); ++i)
			{
			Vertex& v=verts[i];

			v=v+Vertex(-0.5, -0.5, -0.5);

		// Obrot w x
			/*v.x=v.x;
			v.y=v.y*cos(rx*DEGTORAD)-v.z*sin(rx*DEGTORAD);
			v.z=v.y*sin(rx*DEGTORAD)+v.z*cos(rx*DEGTORAD);

		// Obrot w y
			v.x=v.x*cos(ry*DEGTORAD)+v.z*sin(ry*DEGTORAD);
			v.y=v.y;
			v.z=v.z*cos(ry*DEGTORAD)-v.x*sin(ry*DEGTORAD);*/

		// Obrot
			v.x=v.x*cosry+v.y*sinrx*sinry+v.z*cosrx*sinry;
			v.y=v.y*cosrx-v.z*sinrx;
			v.z=-v.x*sinrx+v.y*sinrx*cosry+v.z*cosrx*cosry;

			v=v+Vertex( 0.5,  0.5,  0.5);
			v=v*150.0f+tl;
			}

		for(unsigned int i=1; i<sizeof(verts)/sizeof(Vertex); i+=2)
			{
			Vertex& lv=verts[i-1];
			Vertex& cv=verts[i];

			Drawing::setColor(0x08080808*i);
			Drawing::drawLineShr(lv.x, lv.y, cv.x, cv.y);
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

		rx-=(y-ly);
		ry+=(x-lx);

		lx=x;
		ly=y;
		}

	void mroll(bool down)
		{
		//
		}
	}
