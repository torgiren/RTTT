/*
 * Screen.cpp
 *
 *  Created on: 12-01-2012
 *      Author: crm
 */

#include "screen.h"
#include "drawing.h"

int CUBE_SIZE=64;
int CUBE_DIST=CUBE_SIZE; //CUBE_SIZE*6;
const float CUBE_DIST_RATIO=1.5;

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
	Cube(int x=0, int y=0, int z=0, unsigned int col=0xFFFFFFFF):
		x(x), y(y), z(z), col(col)
		{
		reset();
		}

	Cube(const Cube& c): x(c.x), y(c.y), z(c.z), col(c.col)
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
		verts[ 5]=Vertex(0, 1, 1);
		verts[ 6]=Vertex(1, 1, 1);
		verts[ 7]=Vertex(1, 0, 1);
	// Gora
		verts[ 8]=Vertex(0, 0, 0);
		verts[ 9]=Vertex(0, 0, 1);
		verts[10]=Vertex(1, 0, 1);
		verts[11]=Vertex(1, 0, 0);
	// Dol
		verts[12]=Vertex(0, 1, 0);
		verts[13]=Vertex(1, 1, 0);
		verts[14]=Vertex(1, 1, 1);
		verts[15]=Vertex(0, 1, 1);
	// Lewo
		verts[16]=Vertex(0, 0, 0);
		verts[17]=Vertex(0, 1, 0);
		verts[18]=Vertex(0, 1, 1);
		verts[19]=Vertex(0, 0, 1);
	// Prawo
		verts[20]=Vertex(1, 0, 0);
		verts[21]=Vertex(1, 0, 1);
		verts[22]=Vertex(1, 1, 1);
		verts[23]=Vertex(1, 1, 0);


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

	void kpressed(int k);
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
		}

	void update()
		{
		if(WindowEngine::getKeyState(SDLK_LEFT))
			ry++;
		else if(WindowEngine::getKeyState(SDLK_RIGHT))
			ry--;
		if(WindowEngine::getKeyState(SDLK_UP))
			rx++;
		else if(WindowEngine::getKeyState(SDLK_DOWN))
			rx--;
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
					Drawing::setObj((void *)&area[x][y][z]);
					drawCube(area[x][y][z]);
					}
				}
			}
		}

	void setSize(int ss)
		{
		size=ss;

		CUBE_SIZE=(float)SCREENHEIGHT/(size*(CUBE_SIZE+CUBE_DIST*CUBE_DIST_RATIO))/2.0*CUBE_SIZE;
		CUBE_DIST=CUBE_SIZE*CUBE_DIST_RATIO;

		area.resize(size);
		for(int x=0; x<size; ++x)
			{
			area[x].resize(size);
			for(int y=0; y<size; ++y)
				{
				area[x][y].resize(size);
				for(int z=0; z<size; ++z)
					{
					unsigned char col=rand()%255;
					area[x][y][z]=Cube(x, y, z);
					area[x][y][z].col=(col<<16)+(col<< 8)+col;
					}
				}
			}
		}

	//void rotateArb(Vertex& v, const Vertex& start, const Vertex& axis, float ang)
	void rotateArb(Vertex& v, const Vertex& s, const Vertex& a, float ang)
		{
		float sn, cs, x, y, z;
		sincos(ang, sn, cs);

		x=(s.x*(a.y*a.y+a.z*a.z)-a.x*(s.y*a.y+s.z*a.z-a.x*v.x-a.y*v.y-a.z*v.z))*(1-cs)+v.x*cs+(-s.z*a.y + s.y*a.z - a.z*v.y + a.y*v.z)*sn;
		y=(s.y*(a.x*a.x+a.z*a.z)-a.y*(s.x*a.x+s.z*a.z-a.x*v.x-a.y*v.y-a.z*v.z))*(1-cs)+v.y*cs+( s.z*a.x - s.x*a.z + a.z*v.x - a.x*v.z)*sn;
		z=(s.z*(a.x*a.x+a.y*a.y)-a.z*(s.x*a.x+s.y*a.y-a.x*v.x-a.y*v.y-a.z*v.z))*(1-cs)+v.z*cs+(-s.y*a.x + s.x*a.y - a.y*v.x + a.x*v.y)*sn;
		v.x=x;
		v.y=y;
		v.z=z;
		}

	void drawCube(Cube c)
		{
		Vertex tl(size*(CUBE_DIST+CUBE_SIZE), size*(CUBE_DIST+CUBE_SIZE), size*(CUBE_DIST+CUBE_SIZE));
		Vertex scrtl(SCREENWIDTH/2.0f-	size*(CUBE_DIST+CUBE_SIZE)/2+	CUBE_SIZE/2,
					 SCREENHEIGHT/2.0f-	size*(CUBE_DIST+CUBE_SIZE)/2+	CUBE_SIZE/2,
					 0.0f);

		rx+=mx;
		ry+=my;

		float sx, cx;
		float sy, cy;

		sincos(rx*DEGTORAD, sx, cx);
		sincos(ry*DEGTORAD, sy, cy);

		for(int i=0; i<Cube::VERT_COUNT; i++)
			{
			Vertex& v=c.verts[i];
			v=v-(tl/2.0f);

			rotateArb(v, Vertex(0, 0, 0), Vertex(0, 1, 0), ry*DEGTORAD);
			rotateArb(v, Vertex(0, 0, 0), Vertex(1, 0, 0), rx*DEGTORAD);

			v=v+tl/2+scrtl;
			}

		for(int i=0; i<Cube::VERT_COUNT; i+=4)
			{
			Drawing::setColor(c.col);
			Drawing::drawQuad(c.verts[i+0], c.verts[i+1], c.verts[i+2], c.verts[i+3]);
			}

		mx=0;
		my=0;
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

		Cube *c=(Cube *)Drawing::getObj(x, y);
		if(c)
			printf("kliknieto x, y, z: %d, %d, %d", c->x, c->y, c->z);
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

