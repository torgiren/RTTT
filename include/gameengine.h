#ifndef __GAMEENGINE_H
#define __GAMEENGINE_H
#include "gameenginebase.h"
#include <map>
/**
 *
 * @details Klasa zajmuje się przeliczaniem rozgrywki, położeniem jednostek, systemem walki
 * @author Marcin TORGiren Fabrykowski
 * @brief Główny silnik gry.
 */
class GameEngine: public GameEngineBase
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
		 * @brief Kończy turę
		 * @details Metoda kończąca turę danego gracza. W tej chwili dodawane są jednostki dla "jeszcze" aktualnego gracza.
		 * @return Zwraca numer następnego gracza.
		 */
		uint16 EndTurn();
		/**
		 * @brief Usuwa gracza
		 * @details Metoda usuwająca gracza z rozgrywki. Wszystkie ewentualne jednostki należące do tego gracza stają się jednostkami neutralnymi. Posiadane planety również stają się neutralne.<br/>
		 * Możliwe do wykorzystania zarówno czy odłączeniu się gracza jak również czy pokonaniu danego gracza
		 * @param[in] player Numer gracza który ma zostać usunięty
		 */
		void RemovePlayer(uint16 player);
		/**
		 * @brief Przenosi jednostki z jednej planety na drugą
		 * @details Wykonuje operacje przeniesienia jednostek z planety źródłowej na docelową. Metoda sprawdza czy dana operacja jest możliwa (np: czy <b>num</b> <= liczba_jednostek-1) 
		 * @param[in] src Współrzędne planety źródłowej
		 * @param[in] dst Współrzędne planety docelowej
		 * @param[in] num Liczba jednostek do przeniesienia
		 * @return Zwraca ERRORS::MOVE
		 */
		RETURNS::MOVE Move(const Vertex& src,const Vertex& dst,uint16 num);
		/**
		 * @brief Dodaje nowego gracza do bitwy
		 * @details Dodaje nowego gracza do bitwy i przyporządkowuje mu id socketa na którym ten klient nadaje
		 * @param socket_id Id socketa na którym nadaje gracz
		 * @return Zwraca Numer Gracza jaki dostał nowy gracz
		 */
		uint16 AddPlayer(uint16 socket_id);
		/**
		 * @brief Sprawdza czy gracz może wykonać jakąkolwiek operacje
		 * @details Sprawdza czy numer gracza nadającego z socketa o zadanym id, może wykonywać ruch w tej turze.
		 * @param socket_id Id socketa z którego przyszło żądanie akcji
		 * @return TRUE jeśli to tura tego gracza, FALSE w przeciwnym wypadku
		 */
		bool CanDoAction(uint16 socket_id);
		/**
		 * @brief Sprawdza czy to już koniec gry
		 * @details Sprawdza czy ustawiona jest już flaga zakończenia gry
		 * @return TRUE jeśli to już koniec gry, FALSE w przeciwnym wypadku
		 */
		bool IsEndGame() const;
	private:
		void Win(uint16 gracz);
		bool IsWinning(const Vertex& src) const;
		bool IsWinning(const uint16 gracz) const;
		uint16 NextPlayer();
		bool CanMoveFrom(Planet& planet, uint16 gracz) const;
//		uint16 itsPlayers;
		FightResult itsLastFight;
		std::map<uint16,uint16> itsPlayersMap;
		bool itsEndGame;
};
#endif

