#include "physics.h"

#pragma region AABB
dream::physics::AABB::AABB()
	: m_Min(maths::Vector3()), m_Max(maths::Vector3())
{

}

dream::physics::AABB::AABB(const Rectangle & rectangle)
{
}

dream::physics::AABB::AABB(const maths::Vector2 & m_Min, const maths::Vector2 & m_Max)
	: m_Min(maths::Vector3(m_Min)), m_Max(maths::Vector3(m_Max))
{

}

dream::physics::AABB::AABB(const maths::Vector3 & m_Min, const maths::Vector3 & m_Max)
	: m_Min(maths::Vector3(m_Min)), m_Max(maths::Vector3(m_Max))
{

}

dream::physics::AABB::AABB(float x, float y, float width, float height)
	: m_Min(maths::Vector3(x, y, 0.0f)), m_Max(maths::Vector3(width, height, 0.0f))
{

}

dream::physics::AABB::AABB(float x, float y, float z, float width, float height, float depth)
	: m_Min(maths::Vector3(x, y, z)), m_Max(maths::Vector3(width, height, depth))
{

}

bool dream::physics::AABB::Intersects(const AABB & other) const
{
	return (m_Max > other.m_Min && m_Min < other.m_Max) || (m_Min > other.m_Max && m_Max < other.m_Min);
}

bool dream::physics::AABB::Contains(const maths::Vector2 & point) const
{
	return maths::Vector3(point) > m_Min && maths::Vector3(point) < m_Max;
}

bool dream::physics::AABB::Contains(const maths::Vector3 & point) const
{
	return point > m_Min && point < m_Max;
}

dream::maths::Vector3 dream::physics::AABB::Center() const
{
	return (m_Max + m_Min) * 0.5f;
}


bool dream::physics::AABB::operator==(const AABB & other) const
{
	return m_Min == other.m_Min && m_Max == other.m_Max;
}

bool dream::physics::AABB::operator!=(const AABB & other) const
{
	return !(*this == other);
}

bool dream::physics::AABB::operator<(const AABB & other) const
{
	return m_Max < other.m_Min;
}

bool dream::physics::AABB::operator>(const AABB & other) const
{
	return m_Min > other.m_Max;
}
#pragma endregion

#pragma region Rectangle
dream::physics::Rectangle::Rectangle()	
{
}

dream::physics::Rectangle::Rectangle(AABB & aabb)
{
	m_X = aabb.m_Min.m_X;
	m_Y = aabb.m_Min.m_Y;

	m_Width = aabb.GetSize().m_X;
	m_Height = aabb.GetSize().m_Y;
}

dream::physics::Rectangle::Rectangle(const maths::Vector2 & position, const maths::Vector2 & size)
{
	m_X = position.m_X;
	m_Y = position.m_Y;

	m_Width = size.m_X;
	m_Height = size.m_Y;
}

dream::physics::Rectangle::Rectangle(float x, float y, float width, float height)
{
	m_X = x;
	m_Y = y;
	m_Width = width;
	m_Height = height;
}

bool dream::physics::Rectangle::Intersects(const Rectangle & other) const
{
	maths::Vector2 size(m_X, m_Y);
	maths::Vector2 position(m_Width, m_Height);

	maths::Vector2 otherSize(other.m_X, other.m_Y);
	maths::Vector2 otherPosition(other.m_Width, other.m_Height);

	return (size > otherPosition && position < otherSize) || (position > otherSize && size < otherPosition);
}

bool dream::physics::Rectangle::Contains(const maths::Vector2 & point) const
{
	return point > GetMinimumBound() && point < GetMaximumBound();
}

bool dream::physics::Rectangle::Contains(const maths::Vector3 & point) const
{
	return Contains(maths::Vector2(point.m_X, point.m_Y));
}

bool dream::physics::Rectangle::operator==(const Rectangle & other) const
{
	maths::Vector2 size(m_X, m_Y);
	maths::Vector2 position(m_Width, m_Height);

	maths::Vector2 otherSize(other.m_X, other.m_Y);
	maths::Vector2 otherPosition(other.m_Width, other.m_Height);

	return position == otherPosition && size == otherSize;
}

bool dream::physics::Rectangle::operator!=(const Rectangle & other) const
{
	return !(*this == other);
}

bool dream::physics::Rectangle::operator<(const Rectangle & other) const
{
	maths::Vector2 size(m_X, m_Y);
	maths::Vector2 position(m_Width, m_Height);

	maths::Vector2 otherSize(other.m_X, other.m_Y);
	maths::Vector2 otherPosition(other.m_Width, other.m_Height);

	return size < otherSize;
}

bool dream::physics::Rectangle::operator>(const Rectangle & other) const
{
	maths::Vector2 size(m_X, m_Y);
	maths::Vector2 position(m_Width, m_Height);

	maths::Vector2 otherSize(other.m_X, other.m_Y);
	maths::Vector2 otherPosition(other.m_Width, other.m_Height);

	return size > otherSize;
}
#pragma endregion

#pragma region Circle
dream::physics::Circle::Circle()
{
}

dream::physics::Circle::Circle(const maths::Vector2 & center, float radius)
	: center(center), radius(radius)
{
}

dream::physics::Circle::Circle(float x, float y, float radius)
	: center(maths::Vector2(x, y)), radius(radius)
{
}

float dream::physics::Circle::Penetration(const Circle & other) const
{
	return center.Distance(other.center) - (radius - other.radius);
}

dream::maths::Vector2 dream::physics::Circle::CorrectPen(const Circle & other) const
{
	maths::Vector2 n = (center - other.center) / center.Distance(other.center);
	return n * Penetration(other);	
}

bool dream::physics::Circle::Intersects(const Circle & other) const
{
	return center.Distance(other.center) <= radius + other.radius;
}

bool dream::physics::Circle::Contains(const maths::Vector2 & point) const
{
	return center.Distance(point) < 0;
}

bool dream::physics::Circle::Contains(const maths::Vector3 & point) const
{
	return center.Distance(maths::Vector2(point.m_X, point.m_Y)) < 0;
}

bool dream::physics::Circle::operator==(const Circle & other) const
{		
	return radius == other.radius;
}

bool dream::physics::Circle::operator!=(const Circle & other) const
{	
	return radius != other.radius;
}

bool dream::physics::Circle::operator<(const Circle & other) const
{
	return radius < other.radius;
}

bool dream::physics::Circle::operator>(const Circle & other) const
{
	return radius > other.radius;
}
#pragma endregion