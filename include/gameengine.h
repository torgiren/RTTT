#ifndef __GAMEENGINE_H
#define __GAMEENGINE_H
#include "consts.h"
#include "vertex.h"
#include "planet.h"
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
		 * @brief Destruktor zwalniający pamięć
		 */
		~GameEngine();	
		/**
		 * @brief Konczy ture
		 * @details Metoda kończąca ture danego gracza. W tej chwili dodawane są jednoski dla "jeszcze" aktualnego gracza.
		 * @return Zwraca numer następnego gracza.
		 */
		uint16 EndTurn();
		/**
		 * @brief Aktualny gracz
		 * @details Zwraca numer aktualnego gracza.
		 * @return Numer aktualnego gracza.
		 */
		uint16 ActPlayer() const;
		/**
		 * @brief Przenosi jednoski z jednej planety na drugą
		 * @details Wykonuje operacje przeniesienia jednostek z planety źródłowej na docelową. Metoda sprawdza czy dana operacja jest możliwa (np: czy <b>num</b> <= liczba_jednostek-1) 
		 * @param[in] src Współrzędne planety źródłowej
		 * @param[in] dst Współrzędne planety docelowej
		 * @param[in] num Liczba jednostek do przeniesienia
		 * @return Zwraca ERRORS::MOVE
		 */
		RETURNS::MOVE Move(const Vertex& src,const Vertex& dst,uint16 num);
		/**
		 * @brief Usuwa gracza
		 * @details Metoda usuwajaca gracza z rozgrywki. Wszystkie ewentualne jednostki należące do tego gracza stają się jednosktami neutralnymi. Posiadane planety również stają się neutralne.<br/>
		 * Możliwe do wykorzystania zarówno czy odłączeniu się gracza jak również czy pokananiu danego gracza
		 * @param[in] player Numer gracza który ma zostać usunięty
		 */
		void RemovePlayer(uint16 player);
		Planet& GetPlanet(const Vertex& src);
	private:
		uint16 NextPlayer();
		Planet*** itsPlanety;
		uint16 itsSize;
		uint16 itsPlayers;
		uint16 itsActPlayer;
		FightResult itsLastFight;
};
#endif

