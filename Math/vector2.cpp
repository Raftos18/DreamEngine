#include "vector2.h"

namespace dream
{
	namespace maths
	{
		Vector2::Vector2()
		{
			m_X = 0.0f;
			m_Y = 0.0f;
		}

		Vector2::Vector2(const float & x, const float & y)
		{
			m_X = x;
			m_Y = y;
		}

		Vector2 & Vector2::Add(float value)
		{
			m_X += value;
			m_Y += value;

			return *this;
		}

		Vector2 & Vector2::Add(const Vector2 & other)
		{
			m_X += other.m_X;
			m_Y += other.m_Y;

			return *this;
		}

		Vector2 & Vector2::Subtract(float value)
		{
			m_X -= value;
			m_Y -= value;

			return *this;
		}

		Vector2 & Vector2::Subtract(const Vector2 & other)
		{
			m_X -= other.m_X;
			m_Y -= other.m_Y;

			return *this;
		}

		Vector2 & Vector2::Multiply(float value)
		{
			m_X *= value;
			m_Y *= value;

			return *this;
		}

		Vector2 & Vector2::Multiply(const Vector2 & other)
		{
			m_X *= other.m_X;
			m_Y *= other.m_Y;

			return *this;
		}

		Vector2 & Vector2::Divide(float value)
		{
			m_X /= value;
			m_Y /= value;

			return *this;
		}

		Vector2 & Vector2::Divide(const Vector2 & other)
		{
			m_X /= other.m_X;
			m_Y /= other.m_Y;

			return *this;
		}


		const float & Vector2::GetX()
		{
			return m_X;
		}

		const float & Vector2::GetY()
		{
			return m_Y;
		}


		bool Vector2::operator==(const Vector2 other)
		{
			return m_X == other.m_X && m_Y == other.m_Y;
		}

		bool Vector2::operator!=(const Vector2 other)
		{
			return !(*this == other);
		}

		Vector2 & Vector2::operator+=(float value)
		{
			return Add(value);
		}

		Vector2 & Vector2::operator+=(const Vector2 & other)
		{
			return Add(other);
		}

		Vector2 & Vector2::operator-=(float value)
		{
			return Subtract(value);
		}

		Vector2 & Vector2::operator-=(const Vector2 & other)
		{
			return Subtract(other);
		}

		Vector2 & Vector2::operator*=(float value)
		{
			return Multiply(value);
		}

		Vector2 & Vector2::operator*=(const Vector2 & other)
		{
			return Multiply(other);
		}

		Vector2 & Vector2::operator/=(float value)
		{
			return Divide(value);
		}

		Vector2 & Vector2::operator/=(const Vector2 & other)
		{
			return Divide(other);
		}

		bool Vector2::operator<(const Vector2 & other) const
		{
			return (m_X < other.m_X && m_Y < other.m_Y);
		}

		bool Vector2::operator<=(const Vector2 & other) const
		{
			return (m_X <= other.m_X && m_Y <= other.m_Y);
		}

		bool Vector2::operator>(const Vector2 & other) const
		{
			return (m_X > other.m_X && m_Y > other.m_Y);
		}

		bool Vector2::operator>=(const Vector2 & other) const
		{
			return (m_X >= other.m_X && m_Y >= other.m_Y);
		}

		float Vector2::Magnitude() const
		{
			return sqrt(m_X * m_X + m_Y * m_Y);
		}

		Vector2 Vector2::Normalise() const
		{
			float length = Magnitude();
			return Vector2(m_X / length, m_Y / length);
		}

		float Vector2::Distance(const Vector2 & other) const
		{
			float a = m_X - other.m_X;
			float b = m_Y - other.m_Y;
			return sqrt(a * a + b * b);
		}

		float Vector2::Dot(const Vector2 & other) const
		{
			return m_X * other.m_X + m_Y * other.m_Y;
		}

		Vector2 operator-(Vector2 left, float value)
		{
			return left.Subtract(value);
		}

		Vector2 & operator+(Vector2 left, const Vector2 & right)
		{
			return left.Add(right);
		}

		Vector2 operator+(Vector2 left, float value)
		{
			return left.Add(value);
		}

		Vector2 & operator-(Vector2 left, const Vector2 & right)
		{
			return left.Subtract(right);
		}

		Vector2 operator*(Vector2 left, float value)
		{
			return left.Multiply(value);
		}

		Vector2 & operator*(Vector2 left, const Vector2 & right)
		{
			return left.Multiply(right);
		}

		Vector2 operator/(Vector2 left, float value)
		{
			return left.Divide(value);
		}

		Vector2 & operator/(Vector2 left, const Vector2 & right)
		{
			return left.Divide(right);
		}

		std::ostream & operator<<(std::ostream & stream, const Vector2 vector)
		{
			stream << "Vector(" << vector.m_X << ", " << vector.m_Y << ")";

			return stream;
		}
	}
}