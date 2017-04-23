#pragma once
// Include Std
#include <deque>
#include <vector>
// Include Dream
#include "../Graphics/vertexData.h"
#include "../Math/maths.h"

namespace dream
{
	namespace graphics
	{		
		class IRenderable2D;		

		// Renderer2D interface
		class IRenderer2D
		{
		protected:
			std::vector<maths::Mat4x4> m_transformationStack;		// Holds 4x4 Matrices used for graphics calculations
			const maths::Mat4x4* m_transformationBack;				// Holds a pointer to the last Matrix in the vector for fast access
			
			IRenderer2D() 
			{		
				// Push an identity matrix in the transformation stack
				m_transformationStack.push_back(maths::Mat4x4::Identity());
				// Save pointer to the last object
				m_transformationBack = &m_transformationStack.back();
			}
		public:
			// Used in groups
			inline void Push(const maths::Mat4x4& mat, bool over);
			// Used in groups
			inline void Pop(); 

			virtual void Start() {};
			virtual void Stop() {};			
			virtual void RenderText(const std::string& font, const std::string& text, float x, float y, float scale, unsigned int color) { };
			virtual void Submit(const IRenderable2D* renderable) { };
			virtual void Flush() = 0;			
		};

		// Base class inline impemantations.
		void IRenderer2D::Push(const maths::Mat4x4& mat, bool over)
		{
			if (over)
				m_transformationStack.push_back(mat);
			else
				// In order to tranform the child along with the parent we do this.
				m_transformationStack.push_back(*m_transformationBack * mat);
		}

		void IRenderer2D::Pop()
		{
			if (m_transformationStack.size() > 1)
				m_transformationStack.pop_back();
		}
	}
}


