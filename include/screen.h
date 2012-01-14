/*
 * screen.h
 *
 *  Created on: 12-01-2012
 *      Author: crm
 */

#ifndef SCREEN_H_
#define SCREEN_H_

#include "main.creammy.h"

/**
 * @namespace Screen
 * @brief Chyba cala logika okienka jest tutaj zawarta.
 * @details Obsluga rysowania pola gry, obrotow, klikniecia na klocki~
 */
namespace Screen
	{
	/// @brief Inicjalizacja, ustawia handlery klikniec i wielkosc poziomu na pewna z gory ustalona wartosc~
	void init();
	/// @brief Ibumtralala
	void update();
	/// @brief Rysuje pole gry
	void draw();

	/// @brief Ustawia pole gry na zadana wielkosc
	void setSize(int size);
	}

#endif /* SCREEN_H_ */