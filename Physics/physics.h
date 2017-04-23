#pragma once

#include "../Math/maths.h"

namespace dream {
	namespace physics {
		
		class Rectangle;

		class AABB
		{
		public:
			maths::Vector3 m_Min, m_Max;

			AABB();
			AABB(const Rectangle& rectangle);
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

			inline maths::Vector3 GetSize() const { return maths::Vector3(abs(m_Max.m_X - m_Min.m_X), abs(m_Max.m_Y - m_Min.m_Y), abs(m_Max.m_Z - m_Min.m_Z)); }
		};

		class Rectangle 
		{
		public:
			float m_X, m_Y;
			float m_Width, m_Height;

			Rectangle();
			Rectangle(AABB& aabb);
			Rectangle(const maths::Vector2& position, const maths::Vector2& size);
			Rectangle(float x, float y, float width, float height);

			bool Intersects(const Rectangle& other) const;
			bool Contains(const maths::Vector2& point) const;
			bool Contains(const maths::Vector3& point) const;

			inline maths::Vector2 GetMinimumBound() const { return maths::Vector2(m_X, m_Y) - maths::Vector2(m_Width, m_Height); }
			inline maths::Vector2 GetMaximumBound() const { return maths::Vector2(m_X, m_Y) + maths::Vector2(m_Width, m_Height); }

			bool operator==(const Rectangle& other) const;
			bool operator!=(const Rectangle& other) const;

			bool operator<(const Rectangle& other) const;
			bool operator>(const Rectangle& other) const;
		};

		class Circle 
		{
		public:
			float radius;
			maths::Vector2 center;

			Circle();
			Circle(const maths::Vector2& center, float radius);
			Circle(float x, float y, float radius);

			bool Intersects(const Circle& other) const;
			float Penetration(const Circle& other) const;
			maths::Vector2 CorrectPen(const Circle& other) const;

			bool Contains(const maths::Vector2& point) const;
			bool Contains(const maths::Vector3& point) const;

			bool operator==(const Circle& other) const;
			bool operator!=(const Circle& other) const;

			bool operator<(const Circle& other) const;
			bool operator>(const Circle& other) const;
		};
	}
}
