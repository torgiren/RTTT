#ifndef __GAMEENGINE_H
#define __GAMEENGINE_H
#include "typedefs.h"
#include "point.h"
/**
 *
 * @details Klasa zajmuje się przeliczaniem rozgrywki, położeniem jednostek, systemem walki
 * @author Marcin TORGiren Fabrykowski
 * @brief Główny silnik gry.
 */
class GameEngine
{
	public:
		/**
		 * @brief Tworzy plansze.
		 * @details Konstruktor. Tworzy plansze o zadanym rozmiarze, oraz umieszcza na niej graczy. Plansza ma postać sześcianu o wymiarach: size * size * size. Gracze na planszy rozmieszczeni są w losowy sposób.
		 * @param[in] size Rozmiar planszy.
		 * @param[in] players Liczba graczy biorących udział w rozgrywce
		 */
		GameEngine(uint16 size,uint16 players);
		/**
		 * @brief Konczy ture
		 * @details Metoda kończąca ture danego gracza. W tej chwili dodawane są jednoski dla "jeszcze" aktualnego gracza.
		 * @return Zwraca numer następnego gracza.
		 */
		int NextTurn();
		/**
		 * @brief Aktualny gracz
		 * @details Zwraca numer aktualnego gracz.
		 * @return Numer aktualnego gracza.
		 */
		int ActPlayer() const;
		/**
		 * @brief Przenosi jednoski z jednej planety na drugą
		 * @details Wykonuje operacje przeniesienia jednostek z planety źródłowej na docelową. Metoda sprawdza czy dana operacja jest możliwe (czy <b>num</b> <= liczba_jednostek-1) 
		 * @param[in] src Współrzędne planety źródłowej
		 * @param[in] dst Współrzędne planety docelowej
		 * @param[in] num Liczba jednostek do przeniesienia
		 * @return Zwraca:<ul>
		 * <li>TOO_MUCH - jeśli wybrana ilość jednostek jest większa niż możliwa
		 * <li>OUT_OF_AREA - jeśli wybrane źródło i/lub cel jest poza obszarem gry (normalnie nie występuje)
		 * <li>NOT_ANY - jeśli gracz nie posiada żadnych jednostek na danej planecie źródłowej
		 * </ol>
		 */
		ERRORS::MOVE Move(const Point& src,const Point& dst,uint16 num);
		/**
		 * @brief Usuwa gracza
		 * @details Metoda usuwajaca gracza z rozgrywki. Wszystkie ewentualne jednostki należące do tego gracza stają się jednosktami neutralnymi. Posiadane planety również stają się neutralne.<br/>
		 * Możliwe do wykorzystania zarówno czy odłączeniu się gracza jak również czy pokananiu danego gracza
		 * @param[in] player Numer gracza który ma zostać usunięty
		 */
		void RemovePlayer(uint16 player);
	private:
};
#endif

