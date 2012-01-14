#ifndef WINDOWENGINE_H
#define WINDOWENGINE_H

struct SDL_Surface;

/**
 * @namespace WindowEngine
 * @brief Tworzenie okienka, obsluga zdarzen
 * @details Obsluguje dowolna ilosc bibliotek, po uprzednim dopisaniu ich obslugi. Posiada dwa tryby dzialania: DELAY - stala przerwa miedzy klatkami oraz DELTA - dziala z maksymalna predkoscia. DELTA zalecana jest dla OpenGLa, ktorego tutaj nie ma. Co by nie przeciazac procesora, zalecane jest uzywanie DELAY.
 */
namespace WindowEngine
	{
	enum RenderType {SDL, OPENGL};
	enum WaitType {DELAY, DELTA};

	/**
	 * @brief Inicjalizacja ekranu
	 * @param[in] rt Uzywana biblioteka graficzna. Nie ma nic poza SDLem
	 * @param[in] wt Sposob reagowania na koniec danej klatki.
	 */
	bool init(RenderType rt=SDL, WaitType wt=DELAY);		// Inicjuje wszystko co potrzebne
	/// @brief Obsluga zdarzen
	bool update();
	/// @brief Wyswietlenie na ekran aktualnego stanu bufora
	bool print();
	/// @brief Zamkniecie wszystkiego, co sie da
	bool quit();											// Kasuje wszystko co zbedne

	/// @brief Ustawia flagi okna (SDL). Nie tykac jesli nie wiesz, co robisz.
	void setFlags(unsigned int flags);
	/// @brief Ustawia sposob reagowania na koniec danej klatki
	void setWaitType(WaitType wt);

	RenderType getRenderType();
	WaitType getWaitType();
	float getDelta();

	/// @brief Rejestracja funkcji wywolywanej po wcisnieciu klawisza na klawiaturze
	/// @param handle Wskaznik na funkcje. Argument to kod klawisza
	bool addKeyDownEventHandler(void (*handle)(int));
	/// @brief Rejestracja funkcji wywolywanej po puszczeniu klawisza na klawiaturze
	/// @param handle Wskaznik na funkcje. Argument to kod klawisza
	bool addKeyUpEventHandler(void (*handle)(int));
	/// @brief Rejestracja funkcji wywolywanej po przytrzymaniu klawisza na klawiaturze
	/// @param handle Wskaznik na funkcje. Argument to kod klawisza
	bool addKeyPressedEventHandler(void (*handle)(int));

	/// @brief Rejestracja funkcji wywolywanej po wcisnieciu przycisku myszy
	/// @param handle Wskaznik na funkcje. Argumenty to kod klawisza i polozenie myszy (x, y)
	bool addMouseDownEventHandler(void (*handle)(int, int, int));
	/// @brief Rejestracja funkcji wywolywanej po puszczeniu przycisku myszy
	/// @param handle Wskaznik na funkcje. Argumenty to kod klawisza i polozenie myszy (x, y)
	bool addMouseUpEventHandler(void (*handle)(int, int, int));
	/// @brief Rejestracja funkcji wywolywanej po ruszeniu myszy
	/// @param handle Wskaznik na funkcje. Argumenty to kod klawisza i polozenie myszy (x, y)
	bool addMouseMotionEventHandler(void (*handle)(int, int, int));

	/// @brief Kasuje wskaznik na funkcje \a handle
	void delKeyDownEventHandler(void (*handle)(int));
	/// @brief Kasuje wskaznik na funkcje \a handle
	void delKeyUpEventHandler(void (*handle)(int));
	/// @brief Kasuje wskaznik na funkcje \a handle
	void delKeyPressedEventHandler(void (*handle)(int));

	/// @brief Kasuje wskaznik na funkcje \a handle
	void delMouseDownEventHandler(void (*handle)(int, int, int));
	/// @brief Kasuje wskaznik na funkcje \a handle
	void delMouseUpEventHandler(void (*handle)(int, int, int));
	/// @brief Kasuje wskaznik na funkcje \a handle
	void delMouseMotionEventHandler(void (*handle)(int, int, int));

	/// @brief Kasuje wszystkie wskazniki na funkcje
	void clearEventHandlers();

	/// @brief Zwraca \a true jesli klawisz \a key jest wcisniety
	bool getKeyState(int key);
	/// @brief Zwraca \a true jesli przycisk myszy \a key jest wcisniety
	bool getMouseState(int key);

	/// @brief Zwraca wskaznik na ekran (SDL)
	SDL_Surface* getScreen();
	}

#endif // WINDOWENGINE_H
