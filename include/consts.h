#ifndef CONSTS_H
#define CONSTS_H
#include<stdint.h>
#include<vector>
/**
 * @file consts.h
 */

const int SCREENWIDTH=640;
const int SCREENHEIGHT=480;
const int BPP=32;

const char GAMENAME[]="RTTTT - Risky Tic Tak Toe - Bitwa o Alfa Centauri 4000AD";
const int FPSDELAY=1000/50;

const float DEGTORAD=3.141592653589793f/180.0f;
const float RADTODEG=180.0f/3.141592653589793f;


/**
 * Liczba całkowita o rozmiarze 32bitów
 */
typedef uint32_t uint;
/**
 * Liczba całkowita o rozmiarze 16 bitów
 */
typedef uint16_t uint16;
/**
 * Struktura wiersza logów z walki
 */
typedef std::pair<std::vector<uint16>,std::vector<uint16> >FightResultRow;
/**
 * Wektor wierszy logów z walki
 */
typedef std::vector<FightResultRow> FightResult;

/**
 * Maksymalny poziom okupowanej planety powodujący jej przejęcie
 */
const int OCCUPY_MAX=5;
/**
 * Zawiera komunikaty zwracane z funkcjii
 */
namespace RETURNS
{
	/**
	 * Błędy zwracane przy operacjach przenoszenia jednostek
	 * <ul>
	 * <li>TOO_MUCH - jeśli wybrana ilość jednostek jest większa niż możliwa
	 * <li>OUT_OF_AREA - jeśli wybrane źródło i/lub cel jest poza obszarem gry (normalnie nie występuje)
	 * <li>NOT_ANY - jeśli gracz nie posiada żadnych jednostek na danej planecie źródłowej
	 * <li>MOVE_OK - jeśli przenoszenie jednostek sie powiodło
	 * </ul>
	 */
	enum MOVE {TOO_MUCH, OUT_OF_AREA, NOT_ANY, MOVE_OK};
};

#endif // CONST_H
