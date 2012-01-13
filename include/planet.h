#ifndef __PLANET_H
#define __PLANET_H
#include "typedefs.h"
/**
 * @brief Klasa planety
 * @details Opisuje właściwości planety - elementrarnej jednoski przestrzeni
 * @author Marcin TORGiren Fabrykowski
 */
class Planet
{
	public:
		/**
		 * @brief Tworzy planete
		 * @details Konstruktor. Tworzy neutralna planete z losowa (od 0 do 9) liczbą jednostek
		 */
		Planet();
	private:
		uint16 itsGracz;
		uint16 itsPoziom;
};
#endif
