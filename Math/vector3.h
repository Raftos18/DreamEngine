#pragma once
#include <iostream>
#include "vector2.h"

namespace dream
{
	namespace maths 
	{
		class Vector3
		{
		public:
			float m_X, m_Y, m_Z;
		public:
			Vector3::Vector3();
			Vector3::Vector3(const float& x, const float& y, const float& z);

			Vector3::Vector3(const Vector2& vec2);
			Vector3::Vector3(const float& x, const float& y);

			Vector3& Add(float other);
			Vector3 & Vector3::Add(const Vector3 & other);

			Vector3& Subtract(float other);
			Vector3 & Vector3::Subtract(const Vector3 & other);

			Vector3& Multiply(float other);
			Vector3 & Vector3::Multiply(const Vector3 & other);

			Vector3& Divide(float other);
			Vector3 & Vector3::Divide(const Vector3 & other);

			const float& Vector3::GetX();
			const float& Vector3::GetY();
			const float& Vector3::GetZ();

			friend Vector3 operator+(Vector3 left, float right);
			friend Vector3 & operator+(Vector3 left, const Vector3 & right);

			friend Vector3 operator-(Vector3 left, float right);
			friend Vector3 & operator-(Vector3 left, const Vector3 & right);

			friend Vector3 operator*(Vector3 left, float right);
			friend Vector3 & operator*(Vector3 left, const Vector3 & right);

			friend Vector3 operator/(Vector3 left, float right);
			friend Vector3 & operator/(Vector3 left, const Vector3 & right);

			bool operator==(const Vector3 other) const;
			bool operator<(const Vector3& other) const;
			bool operator<=(const Vector3& other) const;
			bool operator>(const Vector3& other) const;
			bool operator>=(const Vector3& other) const;
			bool operator!=(const Vector3 other) const;

			Vector3& operator+=(float other);
			Vector3& operator+=(const Vector3& other);

			Vector3& operator-=(float other);
			Vector3& operator-=(const Vector3& other);

			Vector3& operator*=(float other);
			Vector3& operator*=(const Vector3& other);

			Vector3& operator/=(float other);
			Vector3& operator/=(const Vector3& other);		

			Vector3 Cross(const Vector3& other) const;
			float Dot(const Vector3& other) const;

			float Magnitude() const;
			Vector3 Normalize() const;
			float Distance(const Vector3& other) const;

			friend std::ostream & operator<<(std::ostream & stream, const Vector3 vector);
		};
	}
}

