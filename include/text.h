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
		Text();
		Text(unsigned int id, float x, float y, float z, float px, float py, Sprite *sSprite, const char *sText, unsigned int w, unsigned int h, int nlSize=16, int spSize=12, int tabSize=32);
		Text(const Text& txt);
		~Text();

		/// @brief Przypisanie tekstu \a str
		Text& operator= (const char *str) {setStr(str); return *this;};
		/// @brief Przypisanie tekstu \a str
		Text& operator= (string str) {setStr(str.c_str()); return *this;};
		/// @brief Dopisanie tekstu \a str
		Text& operator+=(const char *str) {addStr(str); return *this;};
		/// @brief Dopisanie tekstu \a str
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
		//void setText(const char *sText) {setStr(sText);};
		//void setAddText(const char *sText) {addStr(sText);};
		/// @param Przypisanie tekstu \a sStr
		void setStr(const char *sStr);
		/// @param Dopisanie tekstu \a sStr
		void addStr(const char *sStr);
		/// @param Ustawienie wyrównania tekstu
		void setAlign(Align sa) {align=sa;}
		/// @param Ustawienie wyrównania tekstu do lewej
		void setAlignLeft() {align=LEFT;};
		/// @param Ustawienie wyrównania tekstu do środka
		void setAlignCenter() {align=CENTER;};
		/// @param Ustawienie wyrównania tekstu do prawej
		void setAlignRight() {align=RIGHT;};

		void getPos(float& gx, float& gy, float& gz) const {gx=x; gy=y; gz=z;};
		float getX() const {return x;};
		float getY() const {return y;};
		float getZ() const {return z;};
		void getPara(float& gpx, float& gpy) const {gpx=px; gpy=py;};
		//unsigned char getAlpha() const {return min(255, max(0, (int)alpha));};
		const Sprite *getSprite() const {return font;};
		unsigned int getW() const {return w;};
		unsigned int getH() const {return h;};
		void getDim(unsigned int& gw, unsigned int& gh) const {gw=w; gh=h;};
		const char* getText() const {return text;};
		const char* getStr() const {return text;};
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
		int getWordLen(const char *str);		// Dlugosc wyrazu w pikselach
		/// @brief Zwraca długość podanej linii tekstu używając aktualnej czcionki
		int getLineLen(const char *str);		// Dlugosc linii w pikselach
	};

#endif // TEXT_H
