#ifndef SPRITE_SDL_2D_H
#define SPRITE_SDL_2D_H

#include "sprite.h"
#include "main.creammy.h"

/**
 * @class SpriteSDL2D
 * @brief Klasa sprite oparta na SDLu
 * @details Zajmuje się wyświetleniem i wczytaniem obrazka używajac SDLa. 'Gdzieś' jest wersja robiąca to samo dla OpenGLa, ale tutaj nie ma dla niej miejsca.
 * @author crm
 */
class SpriteSDL2D: public Sprite
	{
	private:
		bool loadGfx(const std::string& name);

		SDL_Surface *sprite;
	public:
		/// @param Konstruktor
		/// @param name Nazwa grafiki
		/// @param w Szerokość
		/// @param h Wysokość
		SpriteSDL2D(const std::string& name="", int w=0, int h=0): Sprite(name, w, h), sprite(NULL) {}
		/// @param Destruktor
		virtual ~SpriteSDL2D() {if(sprite) SDL_FreeSurface(sprite);}

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
		void print(float x, float y, float z, int anim, int frame, unsigned char alpha=255u, float px=1.0f, float py=1.0f, unsigned char r=255u, unsigned char g=255u, unsigned char b=255u);
		/// @brief Dobre pytanie. Sam nie wiem.
		/// @details Tak serio to jest to zrobione pod kątem OpenGl'a (array buffer, vbo).
		inline void flush() {};
	};

#endif // SPRITE_SDL_2D_H
