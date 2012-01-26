/*
 * Screen.cpp
 *
 *  Created on: 12-01-2012
 *      Author: crm
 */

#include "screen.h"
#include "drawing.h"
#include "text.h"

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
		x(x), y(y), z(z), col(col), army(0), pct(0.0f)
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

	int army;
	float pct;

	Vertex verts[VERT_COUNT];
	};

/************************************************/
/****************** Funkcje *********************/
/************************************************/
namespace Screen
	{
	void drawCube(Cube& c);

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
	bool moved=false;

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

// Rozgrywka

	Cube *src=NULL;	// Skad?
	Cube *dst=NULL;	// Dokad?
	int army=0;	// Ile?

	Text info(0, 8, 8, 0, 0, 0, NULL, "", SCREENWIDTH-16, SCREENHEIGHT-16);
	Text curr(0, 8, SCREENHEIGHT-60, 0, 0, 0, NULL, "bzium", SCREENWIDTH-16, 16);

	Sprite *bg;

	Vertex tl;//(size*(CUBE_DIST+CUBE_SIZE), size*(CUBE_DIST+CUBE_SIZE), size*(CUBE_DIST+CUBE_SIZE));
	Vertex scrtl;//(SCREENWIDTH/ 2.0f-	size*(CUBE_DIST+CUBE_SIZE)/2.0f,
				// SCREENHEIGHT/2.0f-	size*(CUBE_DIST+CUBE_SIZE)/2.0f,
				// 0.0f);
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

		info.setFont(Sprite::load("data/font_00"));
		curr.setFont(Sprite::load("data/font_00"));
		info.setAlignCenter();
		curr.setAlignCenter();

		bg=Sprite::load("data/bg_01");
		}

	void update()
		{
		if(WindowEngine::getKeyState(SDLK_LEFT))
			my++;
		else if(WindowEngine::getKeyState(SDLK_RIGHT))
			my--;
		if(WindowEngine::getKeyState(SDLK_UP))
			mx++;
		else if(WindowEngine::getKeyState(SDLK_DOWN))
			mx--;

	// Wypisanie informacji
		char csrc[32], cdst[32], carmy[16];
		if(!src)
			sprintf(csrc, "[Wybierz planete]");
		else
			sprintf(csrc, "%02d:%02d:%02d", src->x, src->y, src->z);

		if(!dst)
			sprintf(cdst, "[Wybierz planete]");
		else
			sprintf(cdst, "%02d:%02d:%02d", dst->x, dst->y, dst->z);

		sprintf(carmy, "%d", army);

		info=(string)"Wyslij "+carmy+" jednostek z "+csrc+" do "+cdst;
		}

	void draw()
		{
		Drawing::clearZBuff();
		bg->print(0, 0, 0, 0, 0);

		/*Drawing::setColor(0x00FF0000);
		Drawing::drawLine(Vertex(0, 0, 0), scrtl);
		Drawing::drawLine(Vertex(0, 0, 0), Vertex(SCREENWIDTH, SCREENHEIGHT, 0));
		Drawing::drawLine(Vertex(0, SCREENHEIGHT, 0), Vertex(SCREENWIDTH, 0, 0));*/

		rx+=mx;
		ry+=my;

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

		mx=0;
		my=0;

		info.print();
		curr.print();
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
					unsigned char col=0x88;
					area[x][y][z]=Cube(x, y, z);
					area[x][y][z].col=(col<<16)+(col<< 8)+col; //PLAYER_COLORS[rand()%8];
					if(rand()%100>80)
						{
						area[x][y][z].col=PLAYER_COLORS[rand()%8];
						area[x][y][z].pct=(rand()%5)/4.0f;
						}
					}
				}
			}

		tl=Vertex(size*(CUBE_DIST+CUBE_SIZE), size*(CUBE_DIST+CUBE_SIZE), size*(CUBE_DIST+CUBE_SIZE));
		scrtl=Vertex(SCREENWIDTH/ 2.0f-	size*(CUBE_DIST+CUBE_SIZE)/2.0f+CUBE_DIST/2.0f,
					 SCREENHEIGHT/2.0f-	size*(CUBE_DIST+CUBE_SIZE)/2.0f+CUBE_DIST/2.0f,
					 0.0f);
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

	void drawCube(Cube& c)
		{
		for(int i=0; i<Cube::VERT_COUNT; i++)
			{
			Vertex& v=c.verts[i];
			v=v-(tl/2.0f);

			rotateArb(v, Vertex(0, 0, 0), Vertex(0, 1, 0), my*DEGTORAD);
			rotateArb(v, Vertex(0, 0, 0), Vertex(1, 0, 0), mx*DEGTORAD);

			v=v+(tl/2.0f)+scrtl;
			}

		for(int i=0; i<Cube::VERT_COUNT; i+=4)
			{
			float alpha=max(min(c.verts[i+0].z/(float)((CUBE_SIZE+CUBE_DIST)*size*1.5f), 1.0f), 0.0f);
			unsigned int col=c.col;
			col=Drawing::getColorBlend(col, 0xFF888888, c.pct);
			col=Drawing::getColorBlend(col, 0xFF000000, alpha);
			Drawing::setColor(col);
			Drawing::drawQuad(c.verts[i+0], c.verts[i+1], c.verts[i+2], c.verts[i+3]);

			if(src)
				{
				if(src->x!=c.x || src->y!=c.y || src->z!=c.z);
				else
					{
					Drawing::setColor(PLANET_SRC_COLOR);
					Drawing::drawLine(c.verts[i+0], c.verts[i+1]);
					Drawing::drawLine(c.verts[i+1], c.verts[i+2]);
					Drawing::drawLine(c.verts[i+2], c.verts[i+3]);
					Drawing::drawLine(c.verts[i+3], c.verts[i+0]);
					}
				}
			if(dst)
				{
				if(dst->x!=c.x || dst->y!=c.y || dst->z!=c.z);
				else
					{
					Drawing::setColor(PLANET_DST_COLOR);
					Drawing::drawLine(c.verts[i+0], c.verts[i+1]);
					Drawing::drawLine(c.verts[i+1], c.verts[i+2]);
					Drawing::drawLine(c.verts[i+2], c.verts[i+3]);
					Drawing::drawLine(c.verts[i+3], c.verts[i+0]);
					}
				}

			}

		for(int i=0; i<Cube::VERT_COUNT; i++)
			c.verts[i]=c.verts[i]-scrtl;
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

		if(moved)
			{
			moved=false;
			return;
			}

		if(key==SDL_BUTTON_MIDDLE)
			{
			/***********************************************/
			/***********************************************/
			/** Wyslij informacje o wybranym celu i armii **/
			printf("Wziuuuu~");
			/// @todo /todo \todo --todo ?todo ~~todo~~ \m/todo\m/ to(-_-)do [todo]
			/***********************************************/
			/***********************************************/
			src=NULL;
			dst=NULL;
			return;
			}

		Cube *c=(Cube *)Drawing::getObj(x, y);
		if(c)
			{
			if(key==SDL_BUTTON_LEFT && dst!=c)
				src=c;
			else if(key==SDL_BUTTON_RIGHT && src!=c)
				dst=c;
			}
		}

	void mmove(int x, int y, int key)
		{
		Cube *c=(Cube *)Drawing::getObj(x, y);
		if(c)
			{
			char ccube[32], carmy[16], cpct[16];
			sprintf(ccube, "%02d:%02d:%02d", c->x, c->y, c->z);
			sprintf(carmy, "%d", c->army);
			sprintf(cpct, "%.0f", c->pct*100);
			curr=(string)"Planeta: "+ccube+"\nIlosc jednostek: "+carmy+"\nPrzejete w "+cpct+"%";
			}
		else
			curr="";

		if(!lmb)
			return;

		moved=true;

		mx=-(y-ly);
		my= (x-lx);

		lx=x;
		ly=y;
		}

	void mroll(bool down)
		{
		if(down && army>0)
			army--;
		else if(!down)
			army++;
		}
	}

/************************************************/
/****************** Aktualizacja pola gry *******/
/************************************************/
namespace Screen
	{
	void updateArea(vector<pair<Vertex, Planet> >& items)
		{
		if(items.size()<1)
			return;
		for(vector<pair<Vertex, Planet> >::iterator it=items.begin(); it!=items.end(); ++it)
			{
			Cube& c=area[(int)it->first.x][(int)it->first.y][(int)it->first.z];
			c.pct=it->second.RetPoziom()/(float)OCCUPY_MAX;		// procentowy stopien przejecia
			c.col=PLAYER_COLORS[min(it->second.RetGracz(), (uint16)(sizeof(PLAYER_COLORS)/sizeof(PLAYER_COLORS[0])))];
			}
		}
	}
