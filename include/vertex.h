/**
 * @struct Vertex
 * @brief Prosty vertex/wektor 3D, zawiera podstawowe operacje
 * @details Funkcje rysujące przystosowane są do ułożenia wertexów przeciwnie do ruchu wskazówek zegara (CCW)
 */

#ifndef VERTEX_H
#define VERTEX_H

#include <cmath>

class Vertex
{
	public:
		Vertex(float x, float y, float z):
			x(x), y(y), z(z) {};
		Vertex():
			x(0.0f), y(0.0f), z(0.0f) {};
	
		Vertex& operator=(const Vertex& v)
		{
			x=v.x;
			y=v.y;
			z=v.z;
			return *this;
		}

		bool operator==(const Vertex& v) const
			{
			return (int)x==(int)v.x && (int)y==(int)v.y && (int)z==(int)v.z;
			}

		bool eq2d(const Vertex& v) const
			{
			return (int)x==(int)v.x && (int)y==(int)v.y;
			}

		Vertex operator+(const Vertex& v) const
		{
			return Vertex(x+v.x, y+v.y, z+v.z);
		}

		Vertex operator-(const Vertex& v) const
		{
			return Vertex(x-v.x, y-v.y, z-v.z);
		}

		Vertex operator*(float v) const
		{
			return Vertex(x*v, y*v, z*v);
		}

		Vertex operator/(float v) const
		{
			return Vertex(x/v, y/v, z/v);
		}

	/// @brief Iloczyn wektorowy. Z pewnych powodów pomija z. "Taki ficzer".
		Vertex cross(const Vertex& v) const
		{
			return Vertex(/*y*v.z-z*v.y*/0, /*z*v.x-x*v.z*/0, x*v.y-y*v.x);
		}
	/// @brief Iloczyn wektorowy.
		Vertex crossz(const Vertex& v) const
		{
			return Vertex(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x);
		}

	/// @brief Iloczyn skalarny
		float dot(const Vertex& v) const
		{
			return x*v.x+y*v.y+z*v.z;
		}


	/// @brief Długosć wektora
		float len() const
			{
			return sqrt(x*x+y*y+z*z);
			}

		float x, y, z;
	};

#endif // VERTEX_H
