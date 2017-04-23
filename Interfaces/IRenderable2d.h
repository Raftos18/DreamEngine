#pragma once
#include "./IRenderer2d.h"

#include "../Math/maths.h"
#include "../Graphics/texture.h"
#include "../Graphics/Buffers/arrayBuffer.h"
#include "../Graphics/Buffers/ElementBuffer.h"
#include "../Graphics/Buffers/vertexArray.h"
#include "../Graphics/Shaders/shader.h"

namespace dream
{
	namespace graphics
	{	
		// This should be implemented by any 2D object that wants to be drawn.
		class IRenderable2D
		{
			// TODO:: Make these variables private
		public:
			maths::Vector3 m_Position;						// Holds the position of the renderable
			maths::Vector2 m_Size;							// Holds the size of the renderable
			unsigned int m_Color;							// Holds the color value of the renderable
			std::vector<maths::Vector2> m_UV;				// The texture coordinates of the renderable
			Texture* m_Texture;								// A pointer to the texture 

		public:
			IRenderable2D();			

			IRenderable2D(maths::Vector3 pos, maths::Vector2 size, unsigned int color);

			// Pass it the renderer in which you want to submit the renderable
			virtual void Submit(IRenderer2D* renderer) const;			
			// Sets the color of the renderable(Hex values)
			void SetColor(unsigned int color);
			// Set the color of the renderabel(RGB)
			void SetColor(maths::Vector4& color);			

			// Returns the position of the renderable
			inline const maths::Vector3& GetPosition() const { return m_Position; }
			inline const maths::Vector2& GetSize() const { return m_Size; }
			inline const unsigned int GetColor() const { return m_Color;}
			inline const std::vector<maths::Vector2>& GetUV() const { return m_UV; }
			inline const GLuint getTextID() const { return m_Texture == nullptr ? 0 : m_Texture->GetTextID(); }

		private:
			void SetUVDefaults();				
		};		
	}
}



