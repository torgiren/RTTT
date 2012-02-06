#ifndef VERTEX_H
#define VERTEX_H

#include <cmath>
#include <sstream>
/**
 * @struct Vertex
 * @brief Prosty vertex/wektor 3D, zawiera podstawowe operacje
 * @details Funkcje rysujące przystosowane są do ułożenia wertexów przeciwnie do ruchu wskazówek zegara (CCW)
 * @author crm
 */
class Vertex
{
	public:
		/// @brief Konstruktor
		/// @param x Współrzędna x
		/// @param y Współrzędna y
		/// @param z Współrzędna z
		Vertex(float x, float y, float z):
			x(x), y(y), z(z) {};
		/// @brief Domyślny konstruktor, zeruje wszystkie zmienne
		Vertex():
			x(0.0f), y(0.0f), z(0.0f) {};
	
		/// @brief Przypisanie
		/// @param v Wektor który jest przypisywany
		Vertex& operator=(const Vertex& v)
		{
			x=v.x;
			y=v.y;
			z=v.z;
			return *this;
		}

		/// @brief Porównanie dwóch wektorów
		/// @param v Wektor z którym jest porównywany
		bool operator==(const Vertex& v) const
			{
			return (int)x==(int)v.x && (int)y==(int)v.y && (int)z==(int)v.z;
			}

		/// @brief Porównanie dwóch wektorów z pominięciem współrzędnej \a z
		/// @details Współrzędne są rzutowane na liczbę całkowitą
		/// @param v Wektor z którym jest porównywany
		bool eq2d(const Vertex& v) const
			{
			return (int)x==(int)v.x && (int)y==(int)v.y;
			}

		/// @brief Dodanie dwóch wektorów
		/// @param v Wektor który jest dodawany
		Vertex operator+(const Vertex& v) const
		{
			return Vertex(x+v.x, y+v.y, z+v.z);
		}

		/// @brief Odjęcie dwóch wektorów
		/// @param v Wektor który jest odejmowany
		Vertex operator-(const Vertex& v) const
		{
			return Vertex(x-v.x, y-v.y, z-v.z);
		}

		/// @brief Mnożenie wektora przez liczbę
		/// @param v Liczba
		Vertex operator*(float v) const
		{
			return Vertex(x*v, y*v, z*v);
		}

		/// @brief Dzielenie wektora przez liczbę
		/// @param v Liczba
		Vertex operator/(float v) const
		{
			return Vertex(x/v, y/v, z/v);
		}

		/// @brief Wypisanie wektora
		operator std::string()
		{
			std::stringstream ss;
			ss<<x<<" "<<y<<" "<<z;
			return ss.str();
		};

		/// @brief Iloczyn wektorowy. Z pewnych powodów pomija z. "Taki ficzer".
		/// @param v Wektor
		Vertex cross(const Vertex& v) const
		{
			return Vertex(/*y*v.z-z*v.y*/0, /*z*v.x-x*v.z*/0, x*v.y-y*v.x);
		}
		/// @brief Iloczyn wektorowy.
		/// @param v Wektor
		Vertex crossz(const Vertex& v) const
		{
			return Vertex(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x);
		}

		/// @brief Iloczyn skalarny dwóch wektorów
		/// @param v Wektor
		float dot(const Vertex& v) const
		{
			return x*v.x+y*v.y+z*v.z;
		}


		/// @brief Długosć wektora
		float len() const
			{
			return sqrt(x*x+y*y+z*z);
			}

		/// @brief Współrzędna x
		float x;
		/// @brief Współrzędna y
		float y;
		/// @brief Współrzędna z
		float z;
	};

#endif // VERTEX_H
