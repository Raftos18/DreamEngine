#pragma once

#include <ostream>

namespace dream 
{
	namespace maths
	{
		// The design for all vectors (2,3,4) could be better, like using templates
		// or coupling the classes between them(use Vector2 + plus a Z for Vector3)
		// to create the new vectors.

		class Vector2
		{
		public:
			float m_X, m_Y;
		public:
			Vector2::Vector2();
			Vector2::Vector2(const float & x, const float & y);
			
			Vector2& Add(float value);
			Vector2 & Vector2::Add(const Vector2 & other);

			Vector2& Subtract(float value);
			Vector2 & Vector2::Subtract(const Vector2 & other);
			
			Vector2& Multiply(float value);
			Vector2 & Vector2::Multiply(const Vector2 & other);

			Vector2& Divide(float value);
			Vector2 & Vector2::Divide(const Vector2 & other);
	
			const float& Vector2::GetX();
			const float& Vector2::GetY();
			

			friend Vector2 operator+(Vector2 left, float value);
			friend Vector2 & operator-(Vector2 left, const Vector2 & right);

			friend Vector2 operator-(Vector2 left, float value);
			friend Vector2 & operator+(Vector2 left, const Vector2 & right);

			friend Vector2 operator*(Vector2 left, float value);
			friend Vector2 & operator*(Vector2 left, const Vector2 & right);

			friend Vector2 operator/(Vector2 left, float value);
			friend Vector2 & operator/(Vector2 left, const Vector2 & right);

			bool operator==(const Vector2 other);
			bool operator!=(const Vector2 other);


			Vector2& operator+=(float value);
			Vector2& operator+=(const Vector2& other);

			Vector2& operator-=(float value);
			Vector2& operator-=(const Vector2& other);

			Vector2& operator*=(float value);
			Vector2& operator*=(const Vector2& other);

			Vector2& operator/=(float value);
			Vector2& operator/=(const Vector2& other);

			bool operator<(const Vector2& other) const;
			bool operator<=(const Vector2& other) const;
			bool operator>(const Vector2& other) const;
			bool operator>=(const Vector2& other) const;


			float Magnitude() const;
			Vector2 Normalise() const;
			float Distance(const Vector2& other) const;
			float Dot(const Vector2& other) const;

			friend std::ostream & operator<<(std::ostream & stream, const Vector2 vector);
		};
	}
}
