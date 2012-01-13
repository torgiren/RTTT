#ifndef __TYPEDEFS_H
#define __TYPEDEFS_H
#include <stdint.h>

/**
 * Liczba całkowita o rozmiarze 32bitów
 */
typedef uint32_t uint;
/**
 * Liczba całkowita o rozmiarze 16 bitów
 */
typedef uint16_t uint16;
/**
 * Zawiera wszystkie komunikaty błędów
 */
namespace ERRORS
{
	/**
	 * Błędy zwracane przy operacjach przenoszenia jednostek
	 * <ul>
	 * <li>TOO_MUCH - jeśli wybrana ilość jednostek jest większa niż możliwa
	 * <li>OUT_OF_AREA - jeśli wybrane źródło i/lub cel jest poza obszarem gry (normalnie nie występuje)
	 * <li>NOT_ANY - jeśli gracz nie posiada żadnych jednostek na danej planecie źródłowej
	 * </ul>
	 */
	enum MOVE {TOO_MUCH, OUT_OF_AREA, NOT_ANY};
};
#endif
