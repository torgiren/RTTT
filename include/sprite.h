#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <vector>
#include <map>
#include <set>

#include "windowengine.h"

/**
 * @class Sprite
 * @brief Klasa zajmująca sie wczytaniem, wyświetlaniem i ogólnie obsługą obrazków
 * @details Po niej powinny dziedziczyć wersje zajmujące się implementacją tych operacji w wybranej bibliotece graficznej. Aktualnie zrobione są dla SDL i OpenGL, jednak tutaj dostępny jest tylko SDL.
 * @author crm
 */
class Sprite
	{
	public:
		/**
		 * @class Anim
		 * @brief Informacje o animacji
		 */
		class Anim
			{
			public:
				/**
				 * @class AnimFrame
				 * @brief Klatka animacji
				 * @details Za dużo by pisać, zwykłego śmiertelnika raczej to nie powinno interesować. Czemu jest publiczne, pytasz? A czemu nie~?
				 */
				struct AnimFrame
					{
					/// @brief Konstruktor
					AnimFrame(int x, int y, int w, int h, int spotx=0, int spoty=0, int actx=0, int acty=0, int boxx=0, int boxy=0, int boxw=0, int boxh=0):
						x(x), y(y), w(w), h(h), spotx(spotx), spoty(spoty), actx(actx), acty(acty),
						boxx(boxx), boxy(boxy), boxw(boxw), boxh(boxh) {}
					// x, y, w, h, hotspot, action point~
					int x, y, w, h, spotx, spoty, actx, acty, boxx, boxy, boxw, boxh;
					};
			private:
				std::vector<AnimFrame> animFrames;

				float aspd;
				int fret;
			public:
				/// @brief Konstruktor
				 Anim(float aspd, int fret): aspd(aspd), fret(fret) {};
				/// @brief Destruktor
				~Anim() {clear();}

				/// @brief Czyści wszystkie animacje
				void clear() {animFrames.clear();}

				//void operator+=(int x, int y, int w, int h, int spotx, int spoty, int actx, int acty) {addFrame(x, y, w, h, spotx, spoty, actx, acty);}
				/// @brief Dodaje klatkę o podanych parametrach
				void addFrame(int x, int y, int w, int h, int spotx=0, int spoty=0, int actx=0, int acty=0, int boxx=0, int boxy=0, int boxw=0, int boxh=0) {animFrames.push_back(AnimFrame(x, y, w, h, spotx, spoty, actx, acty, boxx, boxy, boxw, boxh));}
				/// @brief Zwraca klatkę o podanym numerze
				const AnimFrame& getFrame(unsigned int i) {if(i<animFrames.size()) return animFrames[i]; return animFrames.front();};

				/// @brief Ustawia szybkość animacji na podaną wartość
				void setAspd(float sa) {if(sa<0.0f) return; aspd=sa;}
				/// @brief Ustawia klatkę powrotu na podaną
				void setFret(int sa) {if(sa<0 || sa>(int)animFrames.size()) return; fret=sa;}
				/// @brief Zwraca aktualną predkość animacji
				float getAspd() {return aspd;}
				/// @brief Zwraca aktualną klatkę powrotu
				int getFret() {return fret;}

				/// @brief Zwraca ilość klatek
				int getFrameCount() {return animFrames.size();}
			};

		/**
		 * @class SpritePtr
		 * @brief Smart Pointer na sprite. Zwalnia sprite jeśli nikt go nie używa.
		 * @details Dodatkowo posiada obsługę animacji i potrafi odpowiednio zareagowac w przypadku ponownego wczytania sprite dla innej biblioteki graficznej.
		 */
		class SpritePtr
			{
			//private:
			public:
				/// @brief Wskaźnik na grafikę
				Sprite *sprite;

			private:
				int anim;
				float frame, spd;
			public:
				/// @brief Konstruktor domyślny
				 SpritePtr(): sprite(NULL), anim(0), frame(0.0f), spd(-1.0f) {}
				/// @brief Konstruktor
				/// @param s Wskaźnik na grafikę
				 SpritePtr(Sprite *s): sprite(NULL), anim(0), frame(0.0f), spd(-1.0f) {setSprite(s);}
				/// @brief Destruktor
				~SpritePtr() {setSprite(NULL);}

				/// @brief Przypisanie
				inline void operator=(Sprite *s) {setSprite(s);}

				/// @brief Przypisanie
				inline void setSprite(Sprite *s) {if(sprite) sprite->delSpritePtr(this); sprite=s; if(sprite) sprite->addSpritePtr(this);}
				/// @brief Zmiana animacji
				inline void setAnim(int sa) {anim=sa;};
				/// @brief Zmiana szybkości animacji
				inline void setSpd(float ss) {spd=ss;};

				/// @brief Animowanie
				void animate();
				/// @brief Wyświetlenie grafiki
				/**
				 * \param[in] x Współrzędna x
				 * \param[in] y Współrzędna y
				 * \param[in] z Współrzędna z
				 * \param[in] alpha Przeźroczystość, 0-255
				 * \param[in] px Parallax scrolling, poziomy
				 * \param[in] py Parallax scrolling, pionowy
				 * \param[in] r Czerwony
				 * \param[in] g Zielony
				 * \param[in] b Niebieski
				 */
				void print(float x, float y, float z, unsigned char alpha=255u, float px=1.0f, float py=1.0f, unsigned char r=255u, unsigned char g=255u, unsigned char b=255u);
			};
	protected:
		/// @brief Dodaje wskaźnik na smart pointera do listy
		void addSpritePtr(SpritePtr *s) {spritePtrs.insert(s);}
		/// @brief Kasuje wskaźnik na smart pointera z listy
		void delSpritePtr(SpritePtr *s) {spritePtrs.erase(s);}
		/// @brief Przestawia smart pointery z danego Sprite na inny
		/// @param s Nowy sprite
		void setSpritePtrs(Sprite *s);

		/// @brief Wczytywanie grafiki
		/// @details Do zdefiniowania w klasach poniżej
		/// @param name Nazwa
		virtual bool loadGfx(const std::string& name)=0;
		/// @brief Generowanie maski kolizji
		/// @details Tutaj wyłączone celem zaoszczędzenia pamięci
		/// @param pixs Piksele
		/// @param w Szerokość
		/// @param h Wysokość
		/// @param bpp Głębia koloru
		virtual bool loadMask(void *pixs, int w, int h, int bpp);
		/// @brief Wczytywanie animacji
		virtual bool loadAnims(const std::string& name);

		/// @brief Statyczna lista wszystkich wczytanych Sprite'ów
		static std::map<std::string, Sprite *> sprites;

		/// @brief Lista smart pointerów
		std::set<SpritePtr *> spritePtrs;

		/// @brief Nazwa Sprite
		std::string name;
		/// @brief Wymiary
		int w, h;
		/// @brief Maska kolizji
		bool *mask;

		/// @brief Animacje
		std::vector<Anim> anims;
		/// @brief Nazwy animacji
		std::map<std::string, Anim *> animNames;
	public:
		/// @brief Wywołuje \a flush na wszystkich wczytanych Sprite
		static void print();
		/// @brief Kasuje wszystkie sprite
		static void clear();
		/// @brief Ponowne wczytanie Sprite
		/// @details Używać po przestawieniu trybu wyświetlania
		static void reload();

		/// @brief Wczytuje grafikę o podanej nazwie
		static Sprite* load(const std::string& name, bool force=false);

		/// @brief Konstruktor
		/// @param name Nazwa grafiki
		/// @param w Szerokość obrazka
		/// @param h Wysokość obrazka
		Sprite(const std::string& name="", int w=0, int h=0);
		/// @brief Destruktor
		virtual ~Sprite();

		/// @brief Zwraca nazwę grafiki
		const std::string& getName() {return name;}
		/// @brief Zwraca wymiary obrazka
		/// @param[out] gw Szerokość
		/// @param[out] gh Wysokość
		void getDim(int& gw, int& gh) {gw=w; gh=h;}
		/// @brief Zwraca Szerokość
		int getW() {return w;}
		/// @brief Zwraca Wysokość
		int getH() {return h;}
		/// @brief Zwraca animację o numerze \a i
		/// @param i Numer animacji
		Anim& getAnim(unsigned int i) {if(i>anims.size()) return anims[0]; return anims[i];}
		/// @brief Zwraca ilość animacji
		unsigned int getAnimCount() {return anims.size();}

		/// @brief Animuje animację \a anim z prędkością \a spd. Do \a frame wpisuje nową klatkę animacji.
		/// @details Jeśli \a spd jest mniejsze od 0 to używa standardowej szybkości animacji
		/// @param[in] anim Animacja
		/// @param[in,out] frame Klatka początkowa, zmieniane na kolejną
		/// @param[in] spd Szybkość animacji
		virtual void animate(int anim, float& frame, float spd=-1.0f);
		/// @brief Wyświetla Sprite z animacją \a anim i klatką \a frame na współrzędnych x, y, z.
		/// @details Pozostałe parametry są opcjonalne i - obecnie - nieużywane.
		/// @todo Alfa całego obrazka
		/// @todo Parallax scrolling
		/// @todo Barwienie obrazka
		/**
		 * \param[in] x Współrzędna x
		 * \param[in] y Współrzędna y
		 * \param[in] z Współrzędna z
		 * \param[in] anim Numer animacji
		 * \param[in] frame Klatka animacji
		 * \param[in] alpha Przeźroczystość, 0-255
		 * \param[in] px Parallax scrolling, poziomy
		 * \param[in] py Parallax scrolling, pionowy
		 * \param[in] r Czerwony
		 * \param[in] g Zielony
		 * \param[in] b Niebieski
		 */
		virtual void print(float x, float y, float z, int anim, int frame, unsigned char alpha=255u, float px=1.0f, float py=1.0f, unsigned char r=255u, unsigned char g=255u, unsigned char b=255u)=0;
		/// @brief Wyrzucenie bufora
		/// @details Docelowo przeznaczone do OpenGL'a i tablicy wierzchołków. Tutaj nieużywane.
		virtual void flush()=0;
	};

#endif // SPRITE_H
