/*
 * drawing.h
 *
 *  Created on: 12-01-2012
 *      Author: crm
 */

#ifndef DRAWING_H_
#define DRAWING_H_

#include "main.h"

namespace Drawing
	{
	void setSurface(SDL_Surface *srf);
	SDL_Surface* getSurface();

	void setColor(unsigned int sc);
	unsigned int getColor();

	void putPix(int x, int y, float alpha);
	void drawLineWu(float sx, float sy, float tx, float ty, float w=1.0f);
	void drawLineShr(float sx, float sy, float tx, float ty, float w=1.0f);
	}

#endif /* DRAWING_H_ */
