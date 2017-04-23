#pragma once

#include "maths.h"

namespace dream 
{
	namespace maths
	{
		class Mat4x4 
		{			
		public:			
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
			static Mat4x4 Translate(Vector3& translation);
			static Mat4x4 Rotate(float angle, Vector3& axis);
			static Mat4x4 Scale(Vector3& scale);			

			static float* const ValuePtr(Mat4x4 mat) { return &(mat.Columns[0].m_X); }
		};
	}
}