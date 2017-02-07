#pragma once

#include "maths.h"

namespace dream 
{
	namespace maths
	{
		class Mat4x4 
		{			
		public:
			// This union isn't the best solution.
			// But it works
			union
			{
				float m_Elements[4 * 4];
				struct 
				{
					Vector4 Columns[4]; 
				}; 
			};
		public:
			Mat4x4();

			// There is literaly no reason for this
			Mat4x4(float diagonal);
			static Mat4x4 Identity();
			// These should be in a camera class
			static Mat4x4 Orthographic(float left, float right, float bottom, float top, float near, float far);
			static Mat4x4 Perspective(float fov, float aspectRatio, float near, float far);

			Mat4x4& Multiply(const Mat4x4 other);
			Vector3 Multiply(const Vector3 other) const;
			Vector4 Multiply(const Vector4 other) const;

			friend Mat4x4 operator*(Mat4x4 left, const Mat4x4& right);
			friend Vector3 operator*(const Mat4x4& left, const Vector3& right);
			friend Vector4 operator*(const Mat4x4& left, const Vector4& right);

			Mat4x4& operator *=(const Mat4x4 other);

			// These should be more abstracted
			static Mat4x4 Translation(Vector3& translation);
			static Mat4x4 Rotation(float angle, Vector3& axis);
			static Mat4x4 Scale(Vector3& scale);
		};
	}
}