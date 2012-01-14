#ifndef SPRITE_H
#define SPRITE_H

#include <string>
#include <vector>
#include <map>
#include <set>

#include "windowengine.h"

/**
 * @class Sprite
 * @brief Klasa zajmujaca sie wczytaniem, wyswietlaniem i ogolnie obsluga obrazkow
 * @details Po niej powinny dziedziczyc wersje zajmujace sie implementacja tych operacji w wybranej bibliotece graficznej. Aktualnie zrobione sa dla SDL i OpenGL, tutaj dostepny jest tylko SDL.
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
				 * @details Za duzo by pisac, zwyklego smiertelnika raczej to nie powinno interesowac. Czemu jest publiczne, pytasz? A czemu nie~?
				 */
				struct AnimFrame
					{
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
				 Anim(float aspd, int fret): aspd(aspd), fret(fret) {};
				~Anim() {clear();}

				/// @brief Czysci wszystkie animacje
				void clear() {animFrames.clear();}

				//void operator+=(int x, int y, int w, int h, int spotx, int spoty, int actx, int acty) {addFrame(x, y, w, h, spotx, spoty, actx, acty);}
				/// @brief Dodaje klatke o podanych parametrach
				void addFrame(int x, int y, int w, int h, int spotx=0, int spoty=0, int actx=0, int acty=0, int boxx=0, int boxy=0, int boxw=0, int boxh=0) {animFrames.push_back(AnimFrame(x, y, w, h, spotx, spoty, actx, acty, boxx, boxy, boxw, boxh));}
				/// @brief Zwraca klatke o podanym numerze
				const AnimFrame& getFrame(unsigned int i) {if(i<animFrames.size()) return animFrames[i]; return animFrames.front();};

				/// @brief Ustawia szybkosc animacji na podana wartosc
				void setAspd(float sa) {if(sa<0.0f) return; aspd=sa;}
				/// @brief Ustawia klatke powrotu na podana
				void setFret(int sa) {if(sa<0 || sa>(int)animFrames.size()) return; fret=sa;}
				/// @brief Zwraca aktualna predkosc animacji
				float getAspd() {return aspd;}
				/// @brief Zwraca aktualna klatke powrotu
				int getFret() {return fret;}

				/// @brief Zwraca ilosc klatek
				int getFrameCount() {return animFrames.size();}
			};

		/**
		 * @class SpritePtr
		 * @brief Smart Pointer na sprite. Zwalnia sprite jesli nikt go nie uzywa.
		 * @details Dodatkowo posiada obsluge animacji i potrafi odpowiednio zareagowac w przypadku ponownego wczytania sprite dla innej biblioteki graficznej.
		 */
		class SpritePtr
			{
			//private:
			public:
				Sprite *sprite;

			private:
				int anim;
				float frame, spd;
			public:
				 SpritePtr(): sprite(NULL), anim(0), frame(0.0f), spd(-1.0f) {}
				 SpritePtr(Sprite *s): sprite(NULL), anim(0), frame(0.0f), spd(-1.0f) {setSprite(s);}
				~SpritePtr() {setSprite(NULL);}

				inline void operator=(Sprite *s) {setSprite(s);}

				inline void setSprite(Sprite *s) {if(sprite) sprite->delSpritePtr(this); sprite=s; if(sprite) sprite->addSpritePtr(this);}
				inline void setAnim(int sa) {anim=sa;};
				inline void setSpd(float ss) {spd=ss;};

				void animate();
				void print(float x, float y, float z, unsigned char alpha=255u, float px=1.0f, float py=1.0f, unsigned char r=255u, unsigned char g=255u, unsigned char b=255u);
			};
	protected:
		void addSpritePtr(SpritePtr *s) {spritePtrs.insert(s);}
		void delSpritePtr(SpritePtr *s) {spritePtrs.erase(s);}
		void setSpritePtrs(Sprite *s);

		virtual bool loadGfx(const std::string& name)=0;	// Wczytanie grafiki, do zdefiniowania w klasach ponizej
		virtual bool loadMask(void *pixs, int w, int h, int bpp);
		virtual bool loadAnims(const std::string& name);

		static std::map<std::string, Sprite *> sprites;
		//static Engine::RenderType type;

		std::set<SpritePtr *> spritePtrs;

		std::string name;
		int w, h;
		bool *mask;

		std::vector<Anim> anims;
		std::map<std::string, Anim *> animNames;
	public:
		static void print();
		static void clear();
		static void reload();				// Ponowne wczytanie wszystkich grafik

		/// @brief Wczytuje grafike o podanej nazwie
		static Sprite* load(const std::string& name, bool force=false);

		Sprite(const std::string& name="", int w=0, int h=0);
		virtual ~Sprite();

		const std::string& getName() {return name;}
		void getDim(int& gw, int& gh) {gw=w; gh=h;}
		int getW() {return w;}
		int getH() {return h;}
		Anim& getAnim(unsigned int i) {if(i>anims.size()) return anims[0]; return anims[i];}
		unsigned int getAnimCount() {return anims.size();}

		virtual void animate(int anim, float& frame, float spd=-1.0f);
		virtual void print(float x, float y, float z, int anim, int frame, unsigned char alpha=255u, float px=1.0f, float py=1.0f, unsigned char r=255u, unsigned char g=255u, unsigned char b=255u)=0;
		virtual void flush()=0;
	};

#endif // SPRITE_H
