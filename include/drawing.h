/*
 * drawing.h
 *
 *  Created on: 12-01-2012
 *      Author: crm
 */

#ifndef DRAWING_H_
#define DRAWING_H_

#include "main.creammy.h"
#include "vertex.h"

/**
 * @namespace Drawing
 */
namespace Drawing
	{
	/// @brief Czyszczenie zbuffera oraz bufora obiektów
	void clearZBuff();

	/// @brief Ustawia aktualna powierzchnie do rysowania. Nigdzie nie jest sprawdzane, czy nie jest NULLem.
	void setSurface(SDL_Surface *srf);
	/// @brief Zwraca aktualna powierzchnie do rysowania
	SDL_Surface* getSurface();

	/// @brief Ustawia aktualny kolor, 0xAARRGGBB
	void setColor(unsigned int sc);
	/// @brief Zwraca aktualny kolor
	unsigned int getColor();

	/**
	 * @brief Ustawia aktualny obiekt wpisywany do bufora obiektow
	 * @details Bufor obiektow jest rowny co do wielkosci zbufforowi oraz powierzchni. Podczas wstawiania piksela, w tym samym miejscu zapisywana jest informacja o obiekcie tam znajdujacym sie.
	 * @param[in] obj Wskaznik na obiekt. Musisz pamietac, co podsylasz, poniewaz bufor obiektow korzysta z wbudowanego w C++ dynamicznego rzutowania typow (void*)
	 */
	void setObj(void *obj);
	/**
	 * @brief Zwraca wskaznik na obiekt znajdujacy sie na ekranie na pozycji \a x, \a y
	 */
	void* getObj(int x, int y);

	/**
	 * @brief Wstawia na pozycji \a x, \a y, \a z piksel o przezroczystosci rownej \a alpha (od 0.0f do 1.0f).
	 * @details Sprawdzane jest polozenie piksela, czy nie wystaje poza ekran. Wspolrzedna z uzywana jest tylko do zbuffera.
	 */
	void putPix(int x, int y, float z, float alpha);

	/// @brief Rysuje linie laczaca punkty \a a i \a b
	void drawLine(const Vertex& a, const Vertex& b);
	/// @brief Rysuje trojkat laczacy punkty \a a, \a b i \a c
	void drawTriangle(const Vertex& a, const Vertex& b, const Vertex& c);
	/// @brief Rysuje czworokat laczacy punkty \a a, \a b, \a c i \a d
	/// @brief W rzeczywistosci sa to trojkaty a, b, c oraz c, d, a. Proponuje o tym pamietac.
	void drawQuad(const Vertex& a, const Vertex& b, const Vertex& c, const Vertex& d);
	}

#endif /* DRAWING_H_ */
