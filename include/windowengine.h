#ifndef WINDOWENGINE_H
#define WINDOWENGINE_H

struct SDL_Surface;

/**
 * @namespace WindowEngine
 * @brief Tworzenie okienka, obsługa zdarzeń
 * @details Obsługuje dowolną ilość bibliotek, po uprzednim dopisaniu ich obsługi. Posiada dwa tryby działania: DELAY - stała przerwa między klatkami oraz DELTA - działa z maksymalną prędkością. DELTA zalecana jest dla OpenGLa, którego tutaj nie ma. Co by nie przeciążać procesora, zalecane jest używanie DELAY.
 * @author crm
 */
namespace WindowEngine
	{
	enum RenderType {SDL, OPENGL};
	enum WaitType {DELAY, DELTA};

	/**
	 * @brief Inicjalizacja ekranu
	 * @param[in] rt Używana biblioteka graficzna. Nie ma nic poza SDLem
	 * @param[in] wt Sposób reagowania na koniec danej klatki.
	 */
	bool init(RenderType rt=SDL, WaitType wt=DELAY);		// Inicjuje wszystko co potrzebne
	/// @brief Obsługa zdarzeń
	bool update();
	/// @brief Wyświetlenie na ekran aktualnego stanu bufora
	bool print();
	/// @brief Zamknięcie wszystkiego, co się da
	bool quit();											// Kasuje wszystko co zbedne

	/// @brief Ustawia flagi okna (SDL). Nie tykac jeśli nie wiesz, co robisz.
	void setFlags(unsigned int flags);
	/// @brief Ustawia sposób reagowania na koniec danej klatki
	void setWaitType(WaitType wt);

	RenderType getRenderType();
	WaitType getWaitType();
	float getDelta();

	/// @brief Rejestracja funkcji wywoływanej po wciśnięciu klawisza na klawiaturze
	/// @param handle Wskaźnik na funkcję. Argument to kod klawisza
	bool addKeyDownEventHandler(void (*handle)(int));
	/// @brief Rejestracja funkcji wywoływanej po po puszczeniu klawisza na klawiaturze
	/// @param handle Wskaźnik na funkcję. Argument to kod klawisza
	bool addKeyUpEventHandler(void (*handle)(int));
	/// @brief Rejestracja funkcji wywoływanej po po przytrzymaniu klawisza na klawiaturze
	/// @param handle Wskaźnik na funkcję. Argument to kod klawisza
	bool addKeyPressedEventHandler(void (*handle)(int));

	/// @brief Rejestracja funkcji wywoływanej po wcisnieciu przycisku myszy
	/// @param handle Wskaźnik na funkcję. Argumenty to kod klawisza i położenie myszy (x, y)
	bool addMouseDownEventHandler(void (*handle)(int, int, int));
	/// @brief Rejestracja funkcji wywoływanej po puszczeniu przycisku myszy
	/// @param handle Wskaźnik na funkcję. Argumenty to kod klawisza i położenie myszy (x, y)
	bool addMouseUpEventHandler(void (*handle)(int, int, int));
	/// @brief Rejestracja funkcji wywoływanej po ruszeniu myszy
	/// @param handle Wskaźnik na funkcję. Argumenty to kod klawisza i położenie myszy (x, y)
	bool addMouseMotionEventHandler(void (*handle)(int, int, int));

	/// @brief Kasuje wskaźnik na funkcję \a handle
	void delKeyDownEventHandler(void (*handle)(int));
	/// @brief Kasuje wskaźnik na funkcję \a handle
	void delKeyUpEventHandler(void (*handle)(int));
	/// @brief Kasuje wskaźnik na funkcję \a handle
	void delKeyPressedEventHandler(void (*handle)(int));

	/// @brief Kasuje wskaźnik na funkcję \a handle
	void delMouseDownEventHandler(void (*handle)(int, int, int));
	/// @brief Kasuje wskaźnik na funkcję \a handle
	void delMouseUpEventHandler(void (*handle)(int, int, int));
	/// @brief Kasuje wskaźnik na funkcję \a handle
	void delMouseMotionEventHandler(void (*handle)(int, int, int));

	/// @brief Kasuje wszystkie wskaźniki na funkcje
	void clearEventHandlers();

	/// @brief Zwraca \a true jeśli klawisz \a key jest wciśnięty
	bool getKeyState(int key);
	/// @brief Zwraca \a true jeśli przycisk myszy \a key jest wciśnięty
	bool getMouseState(int key);

	/// @brief Zwraca wskaźnik na ekran (SDL)
	SDL_Surface* getScreen();
	}

#endif // WINDOWENGINE_H
