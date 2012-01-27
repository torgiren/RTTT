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

const char IMGEXT[]=".png";
const char ANIMEXT[]=".txt";
const char FONT[]="data/font_00";
const char BACKGROUND[]="data/bg_01";

const float MSG_HIDE_DELAY_FIRST=5.0f;	// sekundy
const float MSG_HIDE_DELAY_NEXT=0.5f;	// sekundy
const unsigned int MSG_MAX_COUNT=8;


/**** Kolory ****/
/// Kolory graczy 1-8
const unsigned int PLAYER_COLORS[]=
		{
		0x00C00000,		// Czerwony
		0x00FEA100,		// Pomarańczowy
		0x00FBFE00,		// Żółty
		0x003FDE00,		// Zielony
		0x0017EECD,		// Cyan
		0x00228FFF,		// Niebieski
		0x005E1FFF, 	// Fioletowy
		0x00CF13EB		// Różowy
		};

/// Kolor wybranej planety zrodlowej
const unsigned int PLANET_SRC_COLOR=0x0058AF58;
/// Kolor wybranej planety docelowej
const unsigned int PLANET_DST_COLOR=0x00C04B4B;


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
	 * <li>MOVE_FIGHT - jeśli odbyła się walka
	 * </ul>
	 */
	enum MOVE {TOO_MUCH, OUT_OF_AREA, NOT_ANY, MOVE_OK,MOVE_FIGHT};
};

#endif // CONST_H
