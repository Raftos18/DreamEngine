#pragma once

#include <iostream>
namespace dream
{
	namespace maths
	{
		class Vector4
		{
		public:
			float m_X, m_Y, m_Z, m_W;
		public:
			Vector4::Vector4();
			Vector4::Vector4(const float& x, const float& y, const float& z, const float& w);

			Vector4 & Vector4::Add(const Vector4 & other);
			Vector4 & Vector4::Subtract(const Vector4 & other);

			Vector4 & Vector4::Multiply(const Vector4 & other);
			Vector4 & Vector4::Divide(const Vector4 & other);

			const float& Vector4::GetX();
			const float& Vector4::GetY();
			const float& Vector4::GetZ();
			const float& Vector4::GetW();

			friend Vector4 & operator-(Vector4 left, const Vector4 & right);
			friend Vector4 & operator+(Vector4 left, const Vector4 & right);

			friend Vector4 & operator*(Vector4 left, const Vector4 & right);
			friend Vector4 & operator/(Vector4 left, const Vector4 & right);

			bool operator==(const Vector4 other);
			bool operator!=(const Vector4 other);

			Vector4& operator+=(const Vector4& other);
			Vector4& operator-=(const Vector4& other);

			Vector4& operator*=(const Vector4& other);
			Vector4& operator/=(const Vector4& other);

			friend std::ostream & operator<<(std::ostream & stream, const Vector4 vector);
		};
	}
}
