#pragma once

#include <iostream>
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

			Vector3 & Vector3::Add(const Vector3 & other);
			Vector3 & Vector3::Subtract(const Vector3 & other);

			Vector3 & Vector3::Multiply(const Vector3 & other);
			Vector3 & Vector3::Divide(const Vector3 & other);

			const float& Vector3::GetX();
			const float& Vector3::GetY();
			const float& Vector3::GetZ();

			friend Vector3 & operator-(Vector3 left, const Vector3 & right);
			friend Vector3 & operator+(Vector3 left, const Vector3 & right);

			friend Vector3 & operator*(Vector3 left, const Vector3 & right);
			friend Vector3 & operator/(Vector3 left, const Vector3 & right);

			bool operator==(const Vector3 other);
			bool operator!=(const Vector3 other);

			Vector3& operator+=(const Vector3& other);
			Vector3& operator-=(const Vector3& other);

			Vector3& operator*=(const Vector3& other);
			Vector3& operator/=(const Vector3& other);

			friend std::ostream & operator<<(std::ostream & stream, const Vector3 vector);
		};
	}
}

