#include "vector3.h"

namespace dream
{
	namespace maths
	{

		Vector3::Vector3()
		{
			m_X = 0.0f;
			m_Y = 0.0f;
			m_Z = 0.0f;
		}

		Vector3::Vector3(const float & x, const float & y, const float & z)
		{
			m_X = x;
			m_Y = y;
			m_Z = z;
		}

		Vector3::Vector3(const Vector2 & vec2)
		{
			m_X = vec2.m_X;
			m_Y = vec2.m_Y;
			m_Z = 0.0f;
		}

		Vector3::Vector3(const float & x, const float & y)
		{
			m_X = x;
			m_Y = y;
			m_Z = 0.0f;
		}

		Vector3 & Vector3::Add(float other)
		{
			m_X += other;
			m_Y += other;
			m_Z += other;

			return *this;
		}

		Vector3 & Vector3::Add(const Vector3 & other)
		{
			m_X += other.m_X;
			m_Y += other.m_Y;
			m_Z += other.m_Y;

			return *this;
		}

		Vector3 & Vector3::Subtract(float other)
		{
			m_X -= other;
			m_Y -= other;
			m_Z -= other;

			return *this;
		}

		Vector3 & Vector3::Subtract(const Vector3 & other)
		{
			m_X -= other.m_X;
			m_Y -= other.m_Y;
			m_Z -= other.m_Y;

			return *this;
		}

		Vector3 & Vector3::Multiply(float other)
		{
			m_X *= other;
			m_Y *= other;
			m_Z *= other;

			return *this;
		}

		Vector3 & Vector3::Multiply(const Vector3 & other)
		{
			m_X *= other.m_X;
			m_Y *= other.m_Y;
			m_Z *= other.m_Y;

			return *this;
		}

		Vector3 & Vector3::Divide(float other)
		{
			m_X /= other;
			m_Y /= other;
			m_Z /= other;

			return *this;
		}

		Vector3 & Vector3::Divide(const Vector3 & other)
		{
			m_X /= other.m_X;
			m_Y /= other.m_Y;
			m_Z /= other.m_Z;

			return *this;
		}

		const float & Vector3::GetX()
		{
			return m_X;
		}

		const float & Vector3::GetY()
		{
			return m_Y;
		}

		const float & Vector3::GetZ()
		{
			return m_Z;
		}

		bool Vector3::operator==(const Vector3 other) const
		{
			return m_X == other.m_X && m_Y == other.m_Y && m_Z == other.m_Z;
		}

		bool Vector3::operator<(const Vector3 & other) const
		{
			return m_X < other.m_X && m_Y < other.m_Y && m_Z < other.m_Z;
		}

		bool Vector3::operator<=(const Vector3 & other) const
		{
			return m_X <= other.m_X && m_Y <= other.m_Y && m_Z <= other.m_Z;
		}

		bool Vector3::operator>(const Vector3 & other) const
		{
			return m_X > other.m_X && m_Y > other.m_Y && m_Z > other.m_Z;
		}

		bool Vector3::operator>=(const Vector3 & other) const
		{
			return m_X >= other.m_X && m_Y >= other.m_Y && m_Z >= other.m_Z;
		}

		bool Vector3::operator!=(const Vector3 other) const
		{
			return !(*this == other);
		}

		Vector3 & Vector3::operator+=(float other)
		{
			return this->Add(other);
		}

		Vector3 & Vector3::operator+=(const Vector3 & other)
		{
			return Add(other);
		}

		Vector3 & Vector3::operator-=(float other)
		{
			return this->Subtract(other);
		}

		Vector3 & Vector3::operator-=(const Vector3 & other)
		{
			return Subtract(other);
		}

		Vector3 & Vector3::operator*=(float other)
		{
			return Multiply(other);
		}

		Vector3 & Vector3::operator*=(const Vector3 & other)
		{
			return Multiply(other);
		}

		Vector3 & Vector3::operator/=(float other)
		{
			return Divide(other);
		}

		Vector3 & Vector3::operator/=(const Vector3 & other)
		{
			return Divide(other);
		}

		Vector3 Vector3::Cross(const Vector3 & other) const
		{
			return Vector3(m_Y * other.m_Z - m_Z * other.m_Y, m_Z * other.m_X - m_X * other.m_Z, m_X * other.m_Y - m_Y * other.m_X);
		}

		float Vector3::Dot(const Vector3 & other) const
		{
			return m_X * other.m_X + m_Y * other.m_Y + m_Z * other.m_Z;
		}

		float Vector3::Magnitude() const
		{
			return sqrt(m_X * m_X + m_Y * m_Y + m_Z * m_Z);
		}

		Vector3 Vector3::Normalize() const
		{
			float length = Magnitude();
			return Vector3(m_X / length, m_Y / length, m_Z / length);
		}

		float Vector3::Distance(const Vector3 & other) const
		{
			float a = m_X - other.m_X;
			float b = m_Y - other.m_Y;
			float c = m_Z - other.m_Z;
			return sqrt(a * a + b * b + c * c);
		}

		Vector3 operator+(Vector3 left, float right)
		{
			return left.Add(right);
		}

		Vector3 & operator+(Vector3 left, const Vector3 & right)
		{
			return left.Add(right);
		}

		Vector3 operator-(Vector3 left, float right)
		{
			return left.Subtract(right);
		}

		Vector3 & operator-(Vector3 left, const Vector3 & right)
		{
			return left.Subtract(right);
		}

		Vector3 operator*(Vector3 left, float right)
		{
			return left.Multiply(right);
		}

		Vector3 & operator*(Vector3 left, const Vector3 & right)
		{
			return left.Multiply(right);
		}

		Vector3 operator/(Vector3 left, float right)
		{
			return left.Divide(right);
		}

		Vector3 & operator/(Vector3 left, const Vector3 & right)
		{
			return left.Divide(right);
		}

		std::ostream & operator<<(std::ostream & stream, const Vector3 vector)
		{
			stream << "Vector(" << vector.m_X << ", " << vector.m_Y << ", " << vector.m_Z  << ")";

			return stream;
		}
	}
}