/*
 * Screen.cpp
 *
 *  Created on: 12-01-2012
 *      Author: crm
 */

#include <list>

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
		x(x), y(y), z(z), col(col), army(0), pct(0.0f), roll(0.0f)
		{
		reset();
		}

	Cube(const Cube& c): x(c.x), y(c.y), z(c.z), col(c.col), roll(0.0f)
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

	float roll;

	Vertex verts[VERT_COUNT];
	};

/************************************************/
/****************** Funkcje *********************/
/************************************************/
namespace Screen
	{
	/// @brief Rysuje kostkę (planetę) na ekran
	void drawCube(Cube& c);

	/// @brief Obsługa kliknięcia
	/// @param x Współrzędna x myszy
	/// @param y Współrzędna y myszy
	/// @param key Kod wciśniętego klawisza
	void mdown(int x, int y, int key);
	/// @brief Obsługa puszczenia przycisku myszy
	/// @param x Współrzędna x myszy
	/// @param y Współrzędna y myszy
	/// @param key Kod wciśniętego klawisza
	void mup(int x, int y, int key);
	/// @brief Obsługa ruchu myszą
	/// @param x Współrzędna x myszy
	/// @param y Współrzędna y myszy
	/// @param key Kod wciśniętego klawisza
	void mmove(int x, int y, int key);
	/// @brief Obsługa kliknięcia rolką
	/// @param down Jest \a prawdą jesli rolka została kliknięta, jeśli została puszczona jest \a fałszem
	void mroll(bool down);
	}

/************************************************/
/****************** Zmienne *********************/
/************************************************/
namespace Screen
	{
	/// @brief Wciśnięty lewy przycisk myszy
	bool lmb=false;
	/// @brief Wciśnięty prawy przycisk myszy
	bool rmb=false;
	/// @brief Wciśnięta rolka
	bool mmb=false;
	/// @brief Myszka ruszyła się
	bool moved=false;

	/// @brief Ostatni x myszy
	int lx=-1;
	/// @brief Ostatni y myszy
	int ly=-1;
	/// @brief Ostatni ruch w x
	float mx=0;
	/// @brief Ostatni ruch w y
	float my=0;

	/// @brief Aktualny obrót w x
	float rx=	0.0f;
	/// @brief Aktualny obrót w y
	float ry=	0.0f;
	/// @brief Aktualny obrót w z
	float rz=	0.0f;
	/// @brief Aktualne przesunięcie w x
	float tx=	0.0f;
	/// @brief Aktualne przesunięcie w y
	float ty=	0.0f;
	/// @brief Aktualna skala
	float scale=1.0f;

	/// @brief Tarcie, zwalnia obrót
	const float FRICTION=0.1f;
	/// @brief Szybkość obrotu w x
	float spdx=	0.0f;
	/// @brief Szybkość obrotu w y
	float spdy= 0.0f;

	float minz, maxz, tminz, tmaxz;

	/// @brief Wielkość pola gry
	int size=4;
	/// @brief Tablica trójwymiarowa pola gry
	vector<vector<vector<Cube> > > area;

// Rozgrywka
	/// @brief ID gracza
	/// @details Używane do rysowania kolorowej ramki wokół poziomu
	int id=0;
	/// @brief Wskaźnik na kostkę (planetę) źródłową
	Cube *src=NULL;
	/// @brief Wskaźnik na kostkę (planetę) docelową
	Cube *dst=NULL;
	/// @brief Ilość jednostek do wysłania
	int army=0;

	/// @brief Górny tekst
	/// @details Informacje o planecie źródłowej, docelowej i ilości jednostek do wysłania
	Text info(0, 8, 8, 0, 0, 0, NULL, "", SCREENWIDTH-16, SCREENHEIGHT-16);
	/// @brief Dolny tekst
	/// @details Informacje o planecie zjandującej się pod kursorem
	Text curr(0, 8, SCREENHEIGHT-60, 0, 0, 0, NULL, "", SCREENWIDTH-16, 16);

	/// @brief Lista wiadomości
	list<Text> msgs;
	/// @brief Odliczanie do zniknięcia kolejnej wiadomości
	float msgTimer=0;
	/// @brief Odliczanie do obracania
	float rotTimer=0;

	/// @brief Wskaźnik na obrazek tła
	Sprite *bg;

	GameEngineClient *engine;

	Vertex tl;
	Vertex scrtl;
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

		info.setFont(Sprite::load(FONT));
		curr.setFont(Sprite::load(FONT));
		info.setAlignCenter();
		curr.setAlignCenter();

		bg=Sprite::load(BACKGROUND);
		}

	void update()
		{
		if(WindowEngine::getKeyState(SDLK_LEFT))
			my-=50*WindowEngine::getDelta();
		else if(WindowEngine::getKeyState(SDLK_RIGHT))
			my+=50*WindowEngine::getDelta();
		if(WindowEngine::getKeyState(SDLK_UP))
			mx+=50*WindowEngine::getDelta();
		else if(WindowEngine::getKeyState(SDLK_DOWN))
			mx-=50*WindowEngine::getDelta();

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

		if(msgs.size()>0)
			{
			if(msgTimer>0.0f)
				msgTimer-=WindowEngine::getDelta();
			else
				{
				msgs.pop_back();
				if(msgs.size()>0)
					msgTimer=MSG_HIDE_DELAY_NEXT;
				}
			}

		if(!lmb)
			{
			mx+=spdx*WindowEngine::getDelta()*100;				// Wartość 100 została otrzymana po wieloletnich obliczeniach.
			my+=spdy*WindowEngine::getDelta()*100;				// Została w nich uwzględniona ilość milisekund w sekundzie.

			spdx-=spdx*FRICTION*WindowEngine::getDelta()*100;
			spdy-=spdy*FRICTION*WindowEngine::getDelta()*100;
			}
		}

	void draw()
		{
		tminz= 1024.0f;
		tmaxz=-1024.0f;

		Drawing::clearZBuff();
		bg->print(0, 0, 0, 0, 0);

		//Drawing::drawLine(Vertex(0, 0, 0), Vertex(SCREENWIDTH, SCREENHEIGHT, 0));
		//Drawing::drawLine(Vertex(0, SCREENHEIGHT, 0), Vertex(SCREENWIDTH, 0, 0));

		Drawing::setColor(PLAYER_COLORS[id]);
		Drawing::drawLine(Vertex(0, 0, 0),						Vertex(SCREENWIDTH-1, 0, 0));
		Drawing::drawLine(Vertex(SCREENWIDTH, 0, 0),			Vertex(SCREENWIDTH-1, SCREENHEIGHT-1, 0));
		Drawing::drawLine(Vertex(SCREENWIDTH-1, SCREENHEIGHT-1, 0),	Vertex(0, SCREENHEIGHT-1, 0));
		Drawing::drawLine(Vertex(0, SCREENHEIGHT-1, 0),	Vertex(0, 0, 0));

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

		minz=tminz;
		maxz=tmaxz;

		mx=0;
		my=0;

		int cy=32;
		for(list<Text>::iterator it=msgs.begin(); it!=msgs.end(); ++it)
			{
			it->setPos(8, cy);
			it->print();
			cy+=it->getH();
			}

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
					area[x][y][z]=Cube(x, y, z);
					area[x][y][z].col=0xFF888888;
					/*if(rand()%100>80)
						{
						area[x][y][z].col=PLAYER_COLORS[rand()%8];
						area[x][y][z].pct=(rand()%5)/4.0f;
						}*/
					}
				}
			}

		tl=Vertex(size*(CUBE_DIST+CUBE_SIZE)-(CUBE_DIST+CUBE_SIZE)/2.0f,
				  size*(CUBE_DIST+CUBE_SIZE)-(CUBE_DIST+CUBE_SIZE)/2.0f,
				  size*(CUBE_DIST+CUBE_SIZE)-(CUBE_DIST+CUBE_SIZE)/2.0f);
		scrtl=Vertex(SCREENWIDTH/ 2.0f-	size*(CUBE_DIST+CUBE_SIZE)/2.0f+CUBE_DIST/2.0f,
					 SCREENHEIGHT/2.0f-	size*(CUBE_DIST+CUBE_SIZE)/2.0f+CUBE_DIST/2.0f,
					 	 	 	 	  -	size*(CUBE_DIST+CUBE_SIZE)/2.0f+CUBE_DIST/2.0f);
		/*printf(" size: %d", size*(CUBE_DIST+CUBE_SIZE));
		printf("   tl: %.02f %.02f %.02f", tl.x, tl.y, tl.z);
		printf("scrtl: %.02f %.02f %.02f", scrtl.x, scrtl.y, scrtl.z);*/
		}

	/// @brief Obrót dowolnego wektora względem dowolny wektor zaczepionego w dowolnym punkcie o dowolny kąt
	/// @param v Wektor do obrócenia
	/// @param s Punkt początkowy
	/// @param a Oś obrotu
	/// @param ang kąt
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
		float left=1024.0f;
		float top=1024.0f;

		for(int i=0; i<Cube::VERT_COUNT; i++)
			{
			Vertex& v=c.verts[i];

			rotateArb(v, tl/2.0f, Vertex(0, 1, 0), my*DEGTORAD);
			rotateArb(v, tl/2.0f, Vertex(1, 0, 0), mx*DEGTORAD);
			//rotateArb(v, Vertex(c.x*(CUBE_DIST+CUBE_SIZE), c.y*(CUBE_DIST+CUBE_SIZE), c.z*(CUBE_DIST+CUBE_SIZE)), Vertex(1, 0, 0), c.roll);

			v=v*scale+scrtl+Vertex(tx, ty, 0.0f);
			v=v+tl/2.0f*(1-scale);

			if(v.z<tminz) tminz=v.z;
			if(v.z>tmaxz) tmaxz=v.z;
			if(v.x<left) left=v.x;
			if(v.y<top) top=v.y;
			}

		if(left>SCREENWIDTH || top>SCREENHEIGHT || left<-(CUBE_DIST+CUBE_SIZE)*scale || top<-(CUBE_DIST+CUBE_SIZE)*scale);
		else
			{
			for(int i=0; i<Cube::VERT_COUNT; i+=4)
				{
				float alpha=max(min(((c.verts[i+0].z-minz)/(maxz-minz)), 1.0f), 0.0f);
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
			}

		for(int i=0; i<Cube::VERT_COUNT; i++)
			{
			Vertex& v=c.verts[i];

			v=v-tl/2.0f*(1-scale);
			v=(v-scrtl-Vertex(tx, ty, 0.0f))/scale;
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

		if(rotTimer<SDL_GetTicks())
			{
			spdx=0;
			spdy=0;
			}

		if(moved)
			{
			moved=false;
			return;
			}

		if(key==SDL_BUTTON_MIDDLE)
			{
			if(src && dst && army)
				{
				engine->SendMove(*src, *dst, army);
				addMessage("Jednostki wyslane.");

				src=NULL;
				dst=NULL;
				army=0;
				}
			else
				addMessage("Wybierz planete zrodlowa, docelowa i ilosc jednostek.");
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
		if(src!=NULL && army>src->army)
			army=src->army;
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


		if(!lmb && !rmb && !mmb)
			return;

		if(!moved)
			{
			moved=true;
			lx=x;
			ly=y;
			}

		if(lmb)
			{
			mx=-(y-ly);
			my= (x-lx);

			if(lmb)
				{
				spdx=mx;
				spdy=my;
				rotTimer=SDL_GetTicks()+200;
				}
			}
		else if(rmb)
			scale=max(0.5f, min(scale+((y-ly)+(x-lx))/100.0f, 5.0f));
		else if(mmb)
			{
			tx+=x-lx;
			ty+=y-ly;

			if(tx<-SCREENWIDTH/2) tx=-SCREENWIDTH/2;
			else if(tx>SCREENWIDTH/2) tx=SCREENWIDTH/2;

			if(ty<-SCREENHEIGHT/2) ty=-SCREENHEIGHT/2;
			else if(ty>SCREENHEIGHT/2) ty=SCREENHEIGHT/2;
			}

		lx=x;
		ly=y;
		}

	void mroll(bool down)
		{
		if(down && army>0)
			army--;
		else if(!down)
			army++;

		if(src!=NULL && army>src->army)
			army=src->army;
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
			unsigned int ncol=PLAYER_COLORS[min(it->second.RetGracz(), (uint16)(sizeof(PLAYER_COLORS)/sizeof(PLAYER_COLORS[0])))];

			if(c.col==PLAYER_COLORS[id] && ncol!=c.col)
				{
				char ccube[32];
				sprintf(ccube, "%02d:%02d:%02d", c.x, c.y, c.z);
				addMessage((std::string)"Planeta "+ccube+" została odbita przez przeciwnika.");
				}
			else if(c.col!=PLAYER_COLORS[id] && ncol==PLAYER_COLORS[id])
				{
				char ccube[32];
				sprintf(ccube, "%02d:%02d:%02d", c.x, c.y, c.z);
				addMessage((std::string)"Planeta "+ccube+" została podbita.");
				}
			else if(c.col==PLAYER_COLORS[id] && it->second.RetOkupant()!=id)
				{
				char ccube[32], cpct[16];
				sprintf(ccube, "%02d:%02d:%02d", c.x, c.y, c.z);
				sprintf(cpct, "%.0f", c.pct*100);
				addMessage((std::string)"Planeta "+ccube+" została zaatakowana! ("+cpct+")");
				}

			c.col=ncol;
			c.army=it->second.RetJednostki();
			c.pct=it->second.RetPoziom()/(float)OCCUPY_MAX;		// procentowy stopien przejecia
			}
		}

	void addMessage(const string& msg)
		{
		if(msgs.size()>MSG_MAX_COUNT)
			msgs.pop_back();
		msgs.push_front(Text(rand(), 8, -32, 0, 0, 0, Sprite::load(FONT), msg.c_str(), SCREENWIDTH-16, 16));
		msgTimer=MSG_HIDE_DELAY_FIRST;
		}

	void setPlayerID(int sid)
		{
		if(sid<0 || sid>=(int)(sizeof(PLAYER_COLORS)/sizeof(PLAYER_COLORS[0])))
			return;
		id=sid;
		}

	void setGameEngineClient(GameEngineClient* e)
		{
		engine=e;
		}
	}
