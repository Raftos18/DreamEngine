#include "Mat4x4.h"
#include "Vector3.h"

#include <cstdint>

namespace dream 
{
	namespace maths
	{
		float ToRadians(float degrees)
		{
			return degrees * (PI / 180.0f);
		}

		Mat4x4::Mat4x4()
		{
			memset(m_Elements, 0, 4 * 4 * sizeof(float));
		}

		Mat4x4::Mat4x4(float diagonal)
		{
			memset(m_Elements, 0, 4 * 4 * sizeof(float));

			m_Elements[0 + 0 * 4] = diagonal;
			m_Elements[1 + 1 * 4] = diagonal;
			m_Elements[2 + 2 * 4] = diagonal;
			m_Elements[3 + 3 * 4] = diagonal;
		}

		Mat4x4 Mat4x4::Identity()
		{
			return Mat4x4(1.0f);
		}

		Mat4x4 dream::maths::Mat4x4::Orthographic(float left, float right, float bottom, float top, float near, float far)
		{
			Mat4x4 result(1.0f);

			result.m_Elements[0 + 0 * 4] = 2.0f / (right - left);

			result.m_Elements[1 + 1 * 4] = 2.0f / (top - bottom);

			result.m_Elements[2 + 2 * 4] = 2.0f / (near - far);

			result.m_Elements[0 + 3 * 4] = (left + right) / (left - right);
			result.m_Elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
			result.m_Elements[2 + 3 * 4] = (far + near) / (far - near);

			return result;
		}

		Mat4x4 dream::maths::Mat4x4::Perspective(float fov, float aspectRatio, float near, float far)
		{
			Mat4x4 result(1.0f);
			
			float q = 1.0f / tan(ToRadians(0.5f * fov));
			float a = q / aspectRatio;
			float b = (near + far) / (near - far);
			float c = (2 * near * far) / (near - far);

			result.m_Elements[0 + 0 * 4] = a;
			result.m_Elements[1 + 1 * 4] = q;
			result.m_Elements[2 + 2 * 4] = b;
			result.m_Elements[2 + 3 * 4] = -1.0f;
			result.m_Elements[3 + 2 * 4] = c;

			return result;
		}

		Mat4x4 & dream::maths::Mat4x4::Multiply(const Mat4x4 other)
		{
			float data[16];
			for (int32_t row = 0; row < 4; row++)
			{
				for (int32_t col = 0; col < 4; col++)
				{
					float sum = 0.0f;
					for (int32_t e = 0; e < 4; e++)
					{
						sum += m_Elements[e + row * 4] * other.m_Elements[col + e * 4];
					}
					data[col + row * 4] = sum;
				}
			}
			memcpy(m_Elements, data, 4 * 4 * sizeof(float));

			return *this;
		}

		Vector3 Mat4x4::Multiply(const Vector3 other) const
		{
			return Vector3(
				Columns[0].m_X * other.m_X + Columns[1].m_X * other.m_Y + Columns[2].m_X * other.m_Z + Columns[3].m_X,
				Columns[0].m_Y * other.m_X + Columns[1].m_Y * other.m_Y + Columns[2].m_Y * other.m_Z + Columns[3].m_Y,
				Columns[0].m_Z * other.m_X + Columns[1].m_Z * other.m_Y + Columns[2].m_Z * other.m_Z + Columns[3].m_Z
			);
		}
		
		Vector4 Mat4x4::Multiply(const Vector4 other) const
		{
			return Vector4(
				Columns[0].m_X * other.m_X + Columns[1].m_X * other.m_Y + Columns[2].m_X * other.m_Z + Columns[3].m_X * other.m_W,
				Columns[0].m_Y * other.m_X + Columns[1].m_Y * other.m_Y + Columns[2].m_Y * other.m_Z + Columns[3].m_Y * other.m_W,
				Columns[0].m_Z * other.m_X + Columns[1].m_Z * other.m_Y + Columns[2].m_Z * other.m_Z + Columns[3].m_Z * other.m_W,
				Columns[0].m_W * other.m_X + Columns[1].m_W * other.m_Y + Columns[2].m_W * other.m_Z + Columns[3].m_W * other.m_W
				);
		}

		Mat4x4 dream::maths::operator*(Mat4x4 left, const Mat4x4 & right)
		{
			return left.Multiply(right);
		}

		Vector3 operator*(const Mat4x4& left, const Vector3& right)
		{
			return left.Multiply(right);
		}

		Vector4 operator*(const Mat4x4& left, const Vector4& right)
		{
			return left.Multiply(right);
		}

		Mat4x4 & dream::maths::Mat4x4::operator*=(const Mat4x4 other)
		{
			return Multiply(other);
		}

		Mat4x4 dream::maths::Mat4x4::Translate(Vector3 & translation)
		{
			Mat4x4 result(1.0f);

			result.m_Elements[0 + 3 * 4] = translation.GetX();
			result.m_Elements[1 + 3 * 4] = translation.GetY();
			result.m_Elements[2 + 3 * 4] = translation.GetZ();
			
			return result;
		}

		Mat4x4 dream::maths::Mat4x4::Rotate(float angle, Vector3 & axis)
		{
			Mat4x4 result(1.0f);

			float r = ToRadians(angle);
			float c = cos(r);
			float s = sin(r);

			float omc = 1.0f - c;

			float x = axis.GetX();
			float y = axis.GetY();
			float z = axis.GetZ();

			result.m_Elements[0 + 0 * 4] = x * x * omc + c;
			result.m_Elements[0 + 1 * 4] = y * x * omc + z * s;
			result.m_Elements[0 + 2 * 4] = x * z * omc - y * s;

			result.m_Elements[1 + 0 * 4] = x * y * omc - z * s;
			result.m_Elements[1 + 1 * 4] = y * y * omc + c;
			result.m_Elements[1 + 2 * 4] = y * z * omc + x * s;
				   
			result.m_Elements[2 + 0 * 4] = x * z * omc + y * s;
			result.m_Elements[2 + 1 * 4] = y * z * omc - x * s;
			result.m_Elements[2 + 2 * 4] = z * z * omc + c;

			return result;
		}

		Mat4x4 dream::maths::Mat4x4::Scale(Vector3 & scale)
		{
			Mat4x4 result(1.0f);

			result.m_Elements[0 + 0 * 4] = scale.GetX();
			result.m_Elements[1 + 1 * 4] = scale.GetY();
			result.m_Elements[2 + 2 * 4] = scale.GetZ();

			return result;
		}

	}
}