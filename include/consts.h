#ifndef CONSTS_H
#define CONSTS_H
#include<stdint.h>
#include<vector>
/**
 * @file consts.h
 */

/// @brief Szerokość okienka
const int SCREENWIDTH=640;
/// @brief Wysokość okienka
const int SCREENHEIGHT=480;
/// @brief Głębia koloru
const int BPP=32;

/// @brief Tytuł okienka z grą
const char GAMENAME[]="RTTT - Risky Tic Tak Toe - Bitwa o Alfa Centauri 4000AD";
/// @brief Przerwa między klatkami (tylko dla DELAY)
const int FPSDELAY=1000/50;

/// @brief Zmienna zamieniająca stopnie na radiany
const float DEGTORAD=3.141592653589793f/180.0f;
/// @brief Zmienna zamieniająca radiany na stopnie
const float RADTODEG=180.0f/3.141592653589793f;

/// @brief Rozszerzenie obrazka
const char IMGEXT[]=".png";
/// @brief Rozszerzenie pliku z animacjami
const char ANIMEXT[]=".txt";
/// @brief Ścieżka do pliku z czcionką
const char FONT[]="data/font_00";
/// @brief Ścieżka do pliku z tłem
const char BACKGROUND[]="data/bg_01";

/// @brief Czas do schowania pierwszej wiadomości, w sekundach
const float MSG_HIDE_DELAY_FIRST=5.0f;	// sekundy
/// @brief Czas do schowania kolejnych wiadomości, w sekundach
const float MSG_HIDE_DELAY_NEXT=0.5f;	// sekundy
/// @brief Maksymalna ilość wiadomości
const unsigned int MSG_MAX_COUNT=8;


/**** Kolory ****/
/// @brief Kolory graczy 1-8
/**
 * <ul>
 * <li>0x00C00000 - <span style="color: #C00000;">Czerwony</span></li>
 * <li>0x00FEA100 - <span style="color: #FEA100;">Pomarańczowy</span></li>
 * <li>0x00FBFE00 - <span style="color: #FBFE00;">Żółty</span></li>
 * <li>0x003FDE00 - <span style="color: #3FDE00;">Zielony</span></li>
 * <li>0x0017EECD - <span style="color: #17EECD;">Cyan</span></li>
 * <li>0x00228FFF - <span style="color: #228FFF;">Niebieski</span></li>
 * <li>0x005E1FFF - <span style="color: #5E1FFF;">Fioletowy</span></li>
 * <li>0x00CF13EB - <span style="color: #CF13EB;">Różowy</span></li>
 * </ul>
 */
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

	typedef uint16 ENDTURN;
	const uint16 NOTHING=1;
	const uint16 NEW_UNIT=2;
	const uint16 FLAG_DOWN=4;
	const uint16 FLAG_UP=8;
	const uint16 PLAYER_OUT=16;
	const uint16 PLAYER_IN=32;
	const uint16 FLAG_ERROR=64;
};

#endif // CONST_H
