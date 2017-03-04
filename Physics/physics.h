#pragma once

#include "../Math/maths.h"

namespace dream {
	namespace physics {
		
		class AABB
		{
		private:
			maths::Vector3 m_Min, m_Max;

			AABB();
			///AABB(const Rectangle& rectangle);
			AABB(const maths::Vector2& min, const maths::Vector2& max);
			AABB(const maths::Vector3& min, const maths::Vector3& max);
			AABB(float x, float y, float width, float height);
			AABB(float x, float y, float z, float width, float height, float depth);

			bool Intersects(const AABB& other) const;
			bool Contains(const maths::Vector2& point) const;
			bool Contains(const maths::Vector3& point) const;

			maths::Vector3 Center() const;

			bool operator==(const AABB& other) const;
			bool operator!=(const AABB& other) const;
			 
			bool operator<(const AABB& other) const;
			bool operator>(const AABB& other) const;

			friend std::ostream& operator<<(std::ostream& stream, const AABB& aabb);

			inline maths::Vector3 GetSize() const { return maths::Vector3(abs(m_Max.m_X - m_Min.m_X), abs(m_Max.m_Y - m_Min.m_Y), abs(m_Max.m_Z - m_Min.m_Z)); }
		};
	}
}
