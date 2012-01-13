#ifndef __POINT_H
#define __POINT_H
#include "typedefs.h"
/**
 * @brief Klasa położenia w przestrzeni
 * @details Obrazuje położenie punktu w przestrzeni planszy
 * @author Marcin TORGiren Fabrykowski
 */
class Point
{
	public:
		/**
		 * Położenie na osi X
		 */
		uint16 itsX;
		/**
		 * Położenie na osi Y
		 */
		uint16 itsY;
		/**
		 * Położenie na osi Z
		 */
		uint16 itsZ;
};
#endif
