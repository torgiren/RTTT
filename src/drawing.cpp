/*
 * drawing.cpp
 *
 *  Created on: 12-01-2012
 *      Author: crm
 */

#include "drawing.h"

/************************************************/
/****************** Zmienne *********************/
/************************************************/
namespace Drawing
	{
	SDL_Surface *srf=NULL;
	unsigned int color=0xFFFFFFFF;
	}

/************************************************/
/****************** Funkcje dodatkowe ***********/
/************************************************/
namespace Drawing
	{
	void setSurface(SDL_Surface *ssrf)
		{
		if(ssrf==NULL)
			printf("Drawing.setSurface: NULL surface, oddziały przygotować się na SIGSEGF!");
		srf=ssrf;
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

	/********************************************/	inline float ipart(float x)
		{
		return (int)x;
		}
	inline float round(float x)
		{
		return ipart(x+0.5);
		}
	inline float fpart(float x)
		{
		return x-ipart(x);
		}
	inline float rfpart(float x)
		{
		return 1-fpart(x);
		}

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
	inline void putPix(int x, int y, float c)
		{
		if(x<0 || x>=srf->w || y<0 || y>=srf->h)
			return;
		unsigned int *pixs=(unsigned int *)srf->pixels;
		unsigned int cc=pixs[x+y*srf->w];
		unsigned char r=((0x00FF0000&color)>>16)*c+((0x00FF0000&cc)>>16)*(1.0f-c);	// Alpha blending~
		unsigned char g=((0x0000FF00&color)>> 8)*c+((0x0000FF00&cc)>> 8)*(1.0f-c);
		unsigned char b=((0x000000FF&color)>> 0)*c+((0x000000FF&cc)>> 0)*(1.0f-c);

		pixs[x+y*srf->w]=0xFF000000+(r<<16)+(g<< 8)+(b<< 0);
		}

	void drawLineWu(float x1, float y1, float x2, float y2, float w)
	//function drawLine(x1,y1,x2,y2) is
		{
		float dx, dy, gradient;
		float xend, yend, xgap, xpxl1, ypxl1, xpxl2, ypxl2;
		float intery;

		dx=x2-x1;
		dy=y2-y1;
		if(abs(dx)<abs(dy))
			{
			swap(x1, y1);
			swap(x2, y2);
			swap(dx, dy);
			}
		if(x2<x1)
			{
			swap(x1, x2);
			swap(y1, y2);
			}

		gradient=dy/dx;

		//printf("x1, y1: %f %f\tx2, y2: %f %f\t dx, dy: %f %f\tgrad: %f\n", x1, y1, x2, y2, dx, dy, gradient);

		// handle first endpoint
		xend=round(x1);
		yend=y1+gradient*(xend-x1);
		xgap=rfpart(x1+0.5);
		xpxl1=xend;  // this will be used in the main loop
		ypxl1=ipart(yend);
		putPix(xpxl1, ypxl1, rfpart(yend)*xgap);
		putPix(xpxl1, ypxl1+1, fpart(yend)*xgap);
		intery=yend+gradient; // first y-intersection for the main loop

		//printf("xend: %f yend: %f xgap: %f xpxl: %f ypxl: %f intery: %f\n", xend, yend, xgap, xpxl1, ypxl1);

		// handle second endpoint
		xend=round (x2);
		yend=y2+gradient*(xend-x2);
		xgap=fpart(x2+0.5);
		xpxl2=xend;  // this will be used in the main loop
		ypxl2=ipart(yend);
		putPix(xpxl2, ypxl2, rfpart(yend)*xgap);
		putPix(xpxl2, ypxl2+1, fpart(yend)*xgap);

		//printf("xend: %f yend: %f xgap: %f xpxl: %f ypxl: %f intery: %f\n", xend, yend, xgap, xpxl2, ypxl2);

		// main loop
		for(float x=xpxl1+1; x<xpxl2; x++)
		//for x from xpxl1 + 1 to xpxl2 - 1 do
			{
			putPix(x, ipart (intery), rfpart(intery));
			putPix(x, ipart (intery)+1, fpart(intery));
			intery=intery+gradient;
			}
		}

	void drawLineShr(float x1, float y1, float x2, float y2, float w)
		{
		if(x1>x2)
			swap(x1, x2);
		if(y1>y2)
			swap(y1, y2);

		float dstx=x2-x1;
		float dsty=y2-y1;
		float len=sqrt(dstx*dstx+dsty*dsty);
		float stepx=dstx/len;
		float stepy=dsty/len;

		//printf("dst: %f %f\tlen: %f\tstep: %f %f\n", dstx, dsty, len, stepx, stepy);

		for(float i=0; i<len; ++i)
			putPix(x1+stepx*i, y1+stepy*i, 1.0f);
		}
	}


