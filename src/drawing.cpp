/*
 * drawing.cpp
 *
 *  Created on: 12-01-2012
 *      Author: crm
 */

#include "drawing.h"

template<typename T> int sgn(T val)
	{
	return (val>T(0))-(val<T(0));
	}

/************************************************/
/****************** Zmienne *********************/
/************************************************/
namespace Drawing
	{
	/// @brief Wskaźnik na ekran
	SDL_Surface *srf=NULL;
	/// @brief Wskaźnik wpisywany do bufora obiektów
	void *obj=NULL;

	/// @brief Bufor głębokości
	float *zbuff=NULL;
	/// @brief Bufor obiektów
	void **obuff=NULL;

	/// @brief Aktualny kolor
	/// @details Kolejność bajtów: 0xAARRGGBB, gdzie AA to alfa, RR to czerwony, GG zielony i BB niebieski.
	unsigned int color=0xFFFFFFFF;

	/// @brief Kierunek światła
	const Vertex light(0.7071, 0.7071, 0);
	}

/************************************************/
/****************** Bufory **********************/
/************************************************/
namespace Drawing
	{
	void clearZBuff()
		{
		//memset((void *)zbuff, 0, srf->w*srf->h*sizeof(float));
		for(int i=0; i<srf->w*srf->h; ++i)
			{
			zbuff[i]=-1024;
			obuff[i]=NULL;
			}
		}
	}

/************************************************/
/****************** Funkcje dodatkowe ***********/
/************************************************/
namespace Drawing
	{
	void setSurface(SDL_Surface *ssrf)
		{
		if(ssrf==NULL)
			printf("Drawing.setSurface: NULL surface, oddzialy przygotowac sie na SIGSEGF!");
		srf=ssrf;

		try
			{
			zbuff=new float[srf->w*srf->h];
			obuff=new void*[srf->w*srf->h];
			}
		catch(std::bad_alloc&)
			{
			printf("Drawing.setSurface: NULL zbuff/obuff, oddzialy przygotowac sie na SIGSEGF!");
			}
		}

	SDL_Surface* getSurface()
		{
		return srf;
		}

	void setColor(unsigned int sc)
		{
		color=sc;
		}

	unsigned int getColor()
		{
		return color;
		}

	unsigned int getColorBlend(unsigned int c1, unsigned int c2, float alpha)
		{
		unsigned char r=((0x00FF0000&c1)>>16)*alpha+((0x00FF0000&c2)>>16)*(1.0f-alpha);
		unsigned char g=((0x0000FF00&c1)>> 8)*alpha+((0x0000FF00&c2)>> 8)*(1.0f-alpha);
		unsigned char b=((0x000000FF&c1)>> 0)*alpha+((0x000000FF&c2)>> 0)*(1.0f-alpha);
		return 0xFF000000+(r<<16)+(g<< 8)+(b<< 0);
		}

	void setObj(void *sobj)
		{
		obj=sobj;
		}

	void* getObj(int x, int y)
		{
		return obuff[x+srf->w*y];
		}

	/********************************************/
	template<class T> inline void swap(T a, T b)
		{
		T tmp=a;
		a=b;
		b=tmp;
		}
	}

/************************************************/
/****************** Funkcje glowne **************/
/************************************************/
namespace Drawing
	{
	inline void putPix(int x, int y, float z, float c)
		{
		int pos=x+y*srf->w;

		if(x<0 || x>=srf->w || y<0 || y>=srf->h)
			return;
		if(z<zbuff[pos])		// Tyle w kwestii zbuffera
			return;
		unsigned int *pixs=(unsigned int *)srf->pixels;
		unsigned int cc=pixs[pos];
		/*unsigned char r=((0x00FF0000&color)>>16)*c+((0x00FF0000&cc)>>16)*(1.0f-c);	// Alpha blending~
		unsigned char g=((0x0000FF00&color)>> 8)*c+((0x0000FF00&cc)>> 8)*(1.0f-c);
		unsigned char b=((0x000000FF&color)>> 0)*c+((0x000000FF&cc)>> 0)*(1.0f-c);*/

		pixs[pos]=getColorBlend(color, cc, c); //0xFF000000+(r<<16)+(g<< 8)+(b<< 0);
		zbuff[pos]=z;
		obuff[pos]=obj;
		}

	void drawLine(const Vertex& a, const Vertex& b)
		{
		if(a.x>b.x)
			swap(a.x, b.x);
		if(a.y>b.y)
			swap(a.y, b.y);
		if(a.z>b.z)
			swap(a.z, b.z);

		float dstx=b.x-a.x;
		float dsty=b.y-a.y;
		float dstz=b.z-a.z;
		float len=sqrt(dstx*dstx+dsty*dsty);
		float stepx=dstx/len;
		float stepy=dsty/len;
		float stepz=dstz/len;

		//printf("dst: %f %f\tlen: %f\tstep: %f %f\n", dstx, dsty, len, stepx, stepy);

		for(float i=0; i<len; ++i)
			putPix(a.x+stepx*i, a.y+stepy*i, a.z+stepz*i, 1.0f);
		}

	/// @brief Sprawdza czy punkty \a p1 i \a p2 leżą po tej samej stronie odcinka \a a, \a b
	/// @details Thx, http://www.blackpawn.com/texts/pointinpoly/default.html
	bool SameSide(const Vertex& p1, const Vertex& p2, const Vertex& a, const Vertex& b)
		{
		Vertex ba(b-a);
		Vertex cp1=ba.cross(p1-a);
		Vertex cp2=ba.cross(p2-a);
		return cp1.dot(cp2)>=0;
		}

	/// @brief Sprawdza, czy punkt \a p leży wewnątrz trójkąta \a a, \a b, \a c
    bool PointInTriangle(const Vertex& p, const Vertex& a, const Vertex& b, const Vertex& c)
		{
    	return (SameSide(p, a, b, c) && SameSide(p, b, a, c) && SameSide(p, c, a, b));
		}

	void drawTriangle(const Vertex& a, const Vertex& b, const Vertex& c)
		{
		if(a.eq2d(b) || b.eq2d(c) || c.eq2d(a))
			return;
		Vertex va=a-b;
		Vertex vb=a-c;
		Vertex v=va.cross(vb);
		if(v.z>0)
			return;
		float left, right;
		float top, bottom;
		float z=(a.z+b.z+c.z)/3.0f;

		left=min(a.x, min(b.x, c.x));
		right=max(a.x, max(b.x, c.x));

		top=min(a.y, min(b.y, c.y));
		bottom=max(a.y, max(b.y, c.y));

		for(int y=top; y<bottom; ++y)
			{
			for(int x=left; x<right; ++x)
				{
				if(PointInTriangle(Vertex(x, y, 0), a, b, c))
					putPix(x, y, z, 1.0f);
				}
			}
		}

	void drawQuad(const Vertex& a, const Vertex& b, const Vertex& c, const Vertex& d)
		{
		Vertex va=a-b;
		Vertex vb=a-c;
		Vertex v=va.crossz(vb);
		float ang=max(v.dot(light)/(va.len()*vb.len()), 0.0f);

		unsigned int ctmp=color;

		unsigned char cr=((0x00FF0000&color)>>16)*(1.0-ang);
		unsigned char cg=((0x0000FF00&color)>> 8)*(1.0-ang);
		unsigned char cb=((0x000000FF&color)>> 0)*(1.0-ang);

		color=(cr<<16)+(cg<< 8)+(cb<< 0);

		drawTriangle(a, b, c);
		drawTriangle(a, c, d);

		color=ctmp;
		}
	}


