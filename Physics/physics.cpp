#include "physics.h"

dream::physics::AABB::AABB()
	: m_Min(maths::Vector3()), m_Max(maths::Vector3())
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

std::ostream & dream::physics::operator<<(std::ostream & stream, const AABB & aabb)
{
	// TODO: insert return statement here
}
