#ifndef __GAMEENGINECLIENT_H
#define __GAMEENGINECLIENT_H
#include "gameenginebase.h"
#include <string>
#include <sstream>
#include "Client.hpp"
#include "screen.h"
/**
 * @brief Klasa silnika gry dla klienta
 * @details Klasa zajmująca się obsługą zachowań gracza po stronie klienta
 * @TODO Rozbudować system przeliczania rozgrywki, aby odciążyć łącze
 * @author Marcin TORGiren Fabrykowski
 */
class GameEngineClient: public GameEngineBase
{
	public:
		/**
		 * @brief Tworzy instancje klienckiego silnika gry
		 * @details Statyczna funkcja, przyjmująca adres serwera do którego będzie się łączył kliencki silnik gry. Tworzy ona połączenie, pobiera stan rozgrywki (rozmiar planszy, swój numer gracza, parametry planet), a następnie na podstawie tych danych tworzy instancje klienckiego silnika gry
		 * @param ip Łańcuch znaków zawierający adres ip serwera gry
		 * @return Wskaźnik na instancję klasy klienckiego silnika gry
		 */
		static GameEngineClient* Create(std::string ip)
		{
			Client* c=Client::create(ip.c_str(),"2330");	
			c->send("Hello");
			bool haveSize=false;
			bool haveNum=false;
			uint16 PlayerNum;
			uint16 MapSize;
			while(!haveSize||!haveNum)
			{
				std::string tmp=c->receive();
				cout<<"Czekam na nr i rozmiar: "<<tmp<<endl;
				if(tmp.compare("empty"))
				{
					std::stringstream ss(tmp);
					std::string first;
					ss>>first;
					if(!first.compare("player"))
					{
						ss>>PlayerNum;
//						cout<<"Wczytałem numer gracza: "<<PlayerNum<<endl;
						haveNum=true;
						Screen::setPlayerID(PlayerNum);
					}
					if(!first.compare("size"))
					{
						ss>>MapSize;
//						cout<<"Wczytałem rozmiar: "<<MapSize<<endl;
						haveSize=true;
					};
				};
				SDL_Delay(100);
			};
			return new GameEngineClient(MapSize,PlayerNum,c);
		};
		
		/**
		 * @brief Główna pętla gry
		 * @details Główna pętla gry, wykonująca się do czasu otrzymania sygnału o zakończeniu rozgrywki. Zajmuje się ona odbieraniem komunikatów od serwera i odpowiedniego reagowania na nie
		 */
		void MainLoop();
		/**
		 * @brief Uaktualnia dane o planecie
		 * @details Ustawia nowe parametry planety znajdującej się pod wskazaniem Vertexa na parametry takie jak zadanej planety
		 * @param dst Wskazanie planety która będzie aktualizowana
		 * @param planet Planeta wzorcowa - po aktualizacji planeta znajdująca się pod dst będzie taka sama jak zadana w parametrze
		 */
		void PlanetUpdate(const Vertex& dst, const Planet& planet);
		/**
		 * @brief Ustawia flagę końca gry
		 * @details Ustawia flagę zakończonej gry
		 */
		void EndGame();
		/**
		 * @brief Wysyła żądanie przesunięcia jednostek
		 * @details Wysyła do serwera żądanie gracza o przeniesienie jednostek z planety pod Vertexem src do planety pod Vertexem dst w liczbie num. W przypadku planet należących do różnych graczy nastąpi walka o tą planetę.
		 * @param src Vertex planety źródłowej
		 * @param dst Vertex planety docelowej
		 * @param num Liczba jednostek do przeniesienia
		 */
		void SendMove(Vertex src, Vertex dst, uint16 num);
		/**
		 * @brief Wysyła żądanie końca tury
		 * @details Wysyła do serwera sygnalizację zakończenia tury przez danego gracza
		 */
		void SendEndTurn();
	private:
		GameEngineClient(uint16 size,uint16 num,Client* client);
		Client* itsC;
		uint16 itsPlayerNum;
		bool itsEndGame;
};
#endif
