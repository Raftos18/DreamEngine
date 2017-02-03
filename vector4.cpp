#include "vector4.h"

namespace dream
{
	namespace maths
	{

		Vector4::Vector4()
		{
			m_X = 0.0f;
			m_Y = 0.0f;
			m_Z = 0.0f;
		}

		Vector4::Vector4(const float & x, const float & y, const float & z, const float& w)
		{
			m_X = x;
			m_Y = y;
			m_Z = z;
			m_W = w;
		}

		Vector4 & Vector4::Add(const Vector4 & other)
		{
			m_X += other.m_X;
			m_Y += other.m_Y;
			m_Z += other.m_Y;
			m_W += other.m_W;

			return *this;
		}

		Vector4 & Vector4::Subtract(const Vector4 & other)
		{
			m_X -= other.m_X;
			m_Y -= other.m_Y;
			m_Z -= other.m_Y;
			m_W -= other.m_W;

			return *this;
		}

		Vector4 & Vector4::Multiply(const Vector4 & other)
		{
			m_X *= other.m_X;
			m_Y *= other.m_Y;
			m_Z *= other.m_Y;
			m_W *= other.m_W;

			return *this;
		}

		Vector4 & Vector4::Divide(const Vector4 & other)
		{
			m_X /= other.m_X;
			m_Y /= other.m_Y;
			m_Z /= other.m_Z;
			m_W /= other.m_W;

			return *this;
		}


		const float & Vector4::GetX()
		{					
			return m_X;		
		}					

		const float & Vector4::GetY()
		{					
			return m_Y;		
		}					
							
		const float & Vector4::GetZ()
		{
			return m_Z;
		}

		const float & Vector4::GetW()
		{
			return m_W;
		}

		bool Vector4::operator==(const Vector4 other)
		{
			return m_X == other.m_X && m_Y == other.m_Y 
				   && m_Z == other.m_Z && m_W == other.m_W;
		}

		bool Vector4::operator!=(const Vector4 other)
		{
			return !(*this == other);
		}

		Vector4 & Vector4::operator+=(const Vector4 & other)
		{
			return Add(other);
		}

		Vector4 & Vector4::operator-=(const Vector4 & other)
		{
			return Subtract(other);
		}

		Vector4 & Vector4::operator*=(const Vector4 & other)
		{
			return Multiply(other);
		}

		Vector4 & Vector4::operator/=(const Vector4 & other)
		{
			return Divide(other);
		}

		Vector4 & operator+(Vector4 left, const Vector4 & right)
		{
			return left.Add(right);
		}

		Vector4 & operator-(Vector4 left, const Vector4 & right)
		{
			return left.Subtract(right);
		}

		Vector4 & operator*(Vector4 left, const Vector4 & right)
		{
			return left.Multiply(right);
		}

		Vector4 & operator/(Vector4 left, const Vector4 & right)
		{
			return left.Divide(right);
		}

		std::ostream & operator<<(std::ostream & stream, const Vector4 vector)
		{
			stream << "Vector(" << vector.m_X << ", " << vector.m_Y << ", " << vector.m_Z << ", " << vector.m_W << ")";

			return stream;
		}
	}
}