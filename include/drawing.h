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
 * @brief Funkcje obsługujące rysowanie
 * @author crm
 */
namespace Drawing
	{
	/// @brief Czyszczenie zbuffera
	/// @details Funkcja również czyści pozostałe bufory (dokładniej mówiąc to jeden bufor, obiektów)
	void clearZBuff();

	/// @brief Ustawia aktualną powierzchnię do rysowania.
	/// @details Nigdzie nie jest sprawdzane, czy nie jest NULLem.
	void setSurface(SDL_Surface *srf);
	/// @brief Zwraca aktualną powierzchnię do rysowania
	SDL_Surface* getSurface();

	/// @brief Ustawia aktualny kolor
	/// @details Kolejność bajtów: 0xAARRGGBB, gdzie AA to alfa, RR to czerwony, GG zielony i BB niebieski
	void setColor(unsigned int sc);
	/// @brief Zwraca aktualny kolor
	unsigned int getColor();
	/// @brief Miesza kolor \a c1 z \a c2 w stosunku \a alpha (1.0 -> 100% c1)
	unsigned int getColorBlend(unsigned int c1, unsigned int c2, float alpha);

	/**
	 * @brief Ustawia aktualny obiekt wpisywany do bufora obiektów
	 * @details Bufor obiektów jest równy co do wielkości zbufforowi oraz powierzchni. Podczas wstawiania piksela, w tym samym miejscu zapisywana jest informacja o obiekcie tam znajdującym się.
	 * @param[in] obj Wskaźnik na dowolny obiekt. Musisz pamiętać, co podsyłasz, ponieważ bufor obiektów korzysta z wbudowanego w C++ dynamicznego rzutowania typów (void*)
	 */
	void setObj(void *obj);
	/**
	 * @brief Zwraca wskaźnik na obiekt znajdujący się na ekranie na pozycji \a x, \a y
	 */
	void* getObj(int x, int y);

	/**
	 * @brief Wstawia na pozycji \a x, \a y, \a z piksel o przeźroczystosci równej \a alpha (od 0.0f do 1.0f).
	 * @details Sprawdzane jest położenie piksela, czy nie wystaje poza ekran. Współrzędna \a z używana jest tylko do zbuffera.
	 */
	void putPix(int x, int y, float z, float alpha);

	/// @brief Rysuje linię łączącą punkty \a a i \a b
	/** Algorytm wygląda następująco:
	 * <ol>
	 * <li>Z twierdzenia Pitagorasa oblicz długość odcinka(<i>l</i>)</li>
	 * <li>Oblicz odległość w poziomie (<i>dx</i>) i w pionie (<i>dy</i>) a następnie podziel je przez długość odcinka</li>
	 * <li>Zapaczynając od jednego z punktów, odpal pętlę <i>l</i> razy</li>
	 * <li>Dla każdej iteracji wypisz piksel w aktualnym punkcie i przesuń się o <i>dx, dy</i></li>
	 * </ol>
	 */
	void drawLine(const Vertex& a, const Vertex& b);

	/// @brief Rysuje trójkąt łączący punkty \a a, \a b i \a c
	/** Algorytm wygląda następująco:
	 * <ol>
	 * <li>Znajdź skrajne punkty i utwórz z nich prostokąt zawierający w sobie cały trójkąt</li>
	 * <li>Przejdź po wszystkich punktach wewnątrz prostokąta</li>
	 * <li>Jeśli punkt jest wewnątrz trójkąta - wstaw piksel, w przeciwnym razie kontynuuj</li>
	 * </ol>
	 */
	void drawTriangle(const Vertex& a, const Vertex& b, const Vertex& c);

	/// @brief Rysuje czworokąt łączący punkty \a a, \a b, \a c i \a d
	/// @brief W rzeczywistości sa to trójkąty a, b, c oraz c, d, a. Proponuję o tym pamiętać.
	void drawQuad(const Vertex& a, const Vertex& b, const Vertex& c, const Vertex& d);
	}

#endif /* DRAWING_H_ */
