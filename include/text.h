#ifndef TEXT_H
#define TEXT_H

#include "main.creammy.h"
#include "sprite.h"

/**
 * @class Text
 * @brief Klasa wyświetlająca tekst
 * @author crm
 *
 * Obsługuje:
 * <ul>
 * <li>Wyrównywanie tekstu do lewej, prawej i środka</li>
 * <li>Zawijanie</li>
 * <li>Różne czcionki</li>
 * <li>Dowolną długość spacji, tabulatora i wysokość linii</li>
 * </ul>
 */
class Text
	{
	public:
		/**
		 * \a LEFT - Wyrównanie do lewej
		 * \a CENTER - Centrowanie tekstu
		 * \a RIGHT - Wyrównanie do prawej
		 */
		enum Align {LEFT, CENTER, RIGHT};
	private:
		unsigned int id;	// Id, do ewentualnego kasowania spod lua
		//int x, y;			// x, y, na intach bo czemu nie~?
		float x, y, z;		// Warstwa	// Pozycje na floacie, tak samo, bo czemu nie~?
		float px, py;		// Parallax
		float alpha;		// Alfa tekstu

		Sprite *font;

		char *text;

		bool upd;		// 1 -> wyswietl ponownie
		//bool inst;
		//float actChr;
		unsigned int w, h;
		int nlSize, spSize, tabSize;	// Wielkosc entera i taba	// Wbrew nazwie nie jest to wielkosc taba tylko rozstaw... 'krawedzi' do ktorych wyrownuje
		Align align;
	public:
		/// @brief Konstruktor domyślny
		Text();
		/// @brief Konstruktor
		/// @param id ID tekstu
		/// @param x Współrzędna x
		/// @param y Współrzędna x
		/// @param z Współrzędna x
		/// @param px Parallax scrolling, poziomy
		/// @param py Parallax scrolling, pionowy
		/// @param sSprite Czcionka
		/// @param sText Tekst
		/// @param w Szerokość
		/// @param h Wysokość (zmienne)
		/// @param nlSize Wysokość linii
		/// @param spSize Długość spacji
		/// @param tabSize Długość tabulatora
		Text(unsigned int id, float x, float y, float z, float px, float py, Sprite *sSprite, const char *sText, unsigned int w, unsigned int h, int nlSize=16, int spSize=12, int tabSize=32);
		/// @brief Konstruktor kopiujący
		/// @param txt Tekst do skopiowania
		Text(const Text& txt);
		/// @brief Destruktor
		~Text();

		/// @brief Przypisanie tekstu \a str
		/// @param str Tekst
		Text& operator= (const char *str) {setStr(str); return *this;};
		/// @brief Przypisanie tekstu \a str
		/// @param str Tekst
		Text& operator= (string str) {setStr(str.c_str()); return *this;};
		/// @brief Dopisanie tekstu \a str
		/// @param str Tekst
		Text& operator+=(const char *str) {addStr(str); return *this;};
		/// @brief Dopisanie tekstu \a str
		/// @param str Tekst
		Text& operator+=(string str) {addStr(str.c_str()); return *this;};

		/// @brief Ustawienie nowej pozycji
		void setPos(float sx, float sy, float sz=0) {x=sx; y=sy; z=sz; upd=1;};
		/// @brief Ustawienie nowej pozycji
		void setX(float sx) {x=sx; upd=1;};
		/// @brief Ustawienie nowej pozycji
		void setY(float sy) {y=sy; upd=1;};
		/// @brief Ustawienie nowej pozycji
		void setZ(float sz) {z=sz; upd=1;};
		/// @brief Ustawienie parametrów parallax scrollingu
		void setPara(float spx, float spy) {px=spx; py=spy; upd=1;};
		/// @brief Ustawienie przeźroczystości tekstu
		void setAlpha(unsigned char sa) {if(alpha==sa) return; alpha=sa; upd=1;};
		/// @brief Ustawienie nowej czcionki
		void setFont(Sprite *sSprite) {setSprite(sSprite);};
		/// @brief Ustawienie nowej czcionki
		void setSprite(Sprite *sSprite);
		/// @brief Ustawienie maksymalnej szerokości tekstu
		void setW(unsigned int sw) {w=sw; upd=1;};
		/// @brief Ustawienie wysokości tekstu. Nie używane do niczego.
		void setH(unsigned int sh) {h=sh;};
		/// @brief Ustawienie wymiarów tekstu
		/// @param sw Szerokość
		/// @param sh Wysokość
		void setDim(unsigned int sw, unsigned int sh) {w=sw; h=sh; upd=1;};
		/// @brief Przypisanie tekstu \a sStr
		/// @param sStr Tekst
		void setStr(const char *sStr);
		/// @brief Dopisanie tekstu \a sStr
		/// @param sStr Tekst
		void addStr(const char *sStr);
		/// @brief Ustawienie wyrównania tekstu
		/// @param sa Typ wyrównania
		void setAlign(Align sa) {align=sa;}
		/// @brief Ustawienie wyrównania tekstu do lewej
		void setAlignLeft() {align=LEFT;};
		/// @brief Ustawienie wyrównania tekstu do środka
		void setAlignCenter() {align=CENTER;};
		/// @brief Ustawienie wyrównania tekstu do prawej
		void setAlignRight() {align=RIGHT;};

		/// @brief Zwraca pozycję tekstu
		/// @param[out] gx Współrzędna x
		/// @param[out] gy Współrzędna y
		/// @param[out] gz Współrzędna z
		void getPos(float& gx, float& gy, float& gz) const {gx=x; gy=y; gz=z;};
		/// @brief Zwraca pozycję x
		float getX() const {return x;};
		/// @brief Zwraca pozycję y
		float getY() const {return y;};
		/// @brief Zwraca pozycję z
		float getZ() const {return z;};
		/// @brief Zwraca parametry Parallax scrollingu
		/// @param[out] gpx Poziomy
		/// @param[out] gpy Pionowy
		void getPara(float& gpx, float& gpy) const {gpx=px; gpy=py;};
		//unsigned char getAlpha() const {return min(255, max(0, (int)alpha));};
		/// @brief Zwraca czcionkę
		const Sprite *getSprite() const {return font;};
		/// @brief Zwraca szerokość
		unsigned int getW() const {return w;};
		/// @brief Zwraca wysokość
		unsigned int getH() const {return h;};
		/// @brief Zwraca wymiary tekstu
		/// @param[out] gw Szerokość
		/// @param[out] gh Wysokość
		void getDim(unsigned int& gw, unsigned int& gh) const {gw=w; gh=h;};
		/// @brief Zwraca tekst
		const char* getText() const {return text;};
		/// @brief Zwraca tekst
		const char* getStr() const {return text;};
		/// @brief Zwraca wyrównanie tekstu
		int getAlign() const {return align;};
		//int getFontSize() const {if(!font) return 0; return font->getAnim(0)->h;};
		/// @brief Zwraca wielkość nowej linii (wysokość linii tekstu)
		int getNlSize() const {return nlSize;};
		/// @brief Zwraca wielkość spacji (ilość pikseli odstępu między znakami)
		int getSpSize() const {return spSize;};
		/// @brief Zwraca wielkość tabulatora
		int getTabSize() const {return tabSize;};

		/// @brief Aktualizacja tekstu
		/// @details Tutaj nieużywane.
		void update();
		/// @brief Wypisanie tekstu
		void print();

		/// @brief Zwraca długość podanego tekstu (do białego znaku) używając aktualnej czcionki
		/// @param str Tekst
		int getWordLen(const char *str);		// Dlugosc wyrazu w pikselach
		/// @brief Zwraca długość podanej linii tekstu używając aktualnej czcionki
		/// @param str Tekst
		int getLineLen(const char *str);		// Dlugosc linii w pikselach
	};

#endif // TEXT_H
