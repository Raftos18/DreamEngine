#pragma once

#include "renderable2d.h"

namespace dream
{
	namespace graphics
	{
		class Sprite : public IRenderable2D
		{
		public:
			Sprite(float x, float y, float width, float height, Vector4& color);
		};

		class StaticSprite : public IRenderable2D
		{
		private:
			// Smart pointers would be a much better choice
			VertexArray* m_VertexArray;
			IndexBuffer* m_IndexBuffer;

			Shader& m_Shader;
		public:
			StaticSprite(float x, float y, float width, float height, Vector4& color, Shader& shader);
			~StaticSprite();

			inline Shader& GetShader() const { return m_Shader; }

			inline const VertexArray* GetVAO() const { return m_VertexArray; }
			inline const IndexBuffer* GetIBO() const { return m_IndexBuffer; }
		};
	} 
}
