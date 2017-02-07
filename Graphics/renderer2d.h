#pragma once
#include <deque>
#include <vector>

//#include "renderable2d.h"
#include "maths.h"

namespace dream
{
	namespace graphics
	{

#define RENDERER_MAX_SPRITES		60000
#define RENDERER_VERTEX_SIZE		sizeof(VertexData)
#define RENDERER_SPRITE_SIZE		RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE		RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICIES_SIZE		RENDERER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX 0
#define SHADER_UV_INDEX 1
#define SHADER_TID_INDEX 2
#define SHADER_COLOR_INDEX 3

		class IRenderable2D;
		//class StaticSprite;

		// Renderer2D interface
		class IRenderer2D
		{
		protected:
			std::vector<maths::Mat4x4> m_transformationStack;
			const maths::Mat4x4* m_transformationBack;

			// Always hold at least the identity matrix in the transformation stack
			IRenderer2D() 
			{
				m_transformationStack.push_back(maths::Mat4x4::Identity());
				m_transformationBack = &m_transformationStack.back();
			}
		public:

			inline void Push(const maths::Mat4x4& mat, bool over);
			inline void Pop(); 

			virtual void Begin() {};
			virtual void End() {};
			virtual void DrawString(const std::string text, const maths::Vector3& position, const maths::Vector4& color) {};
			virtual void Submit(const IRenderable2D* renderable) = 0;
			virtual void Flush() = 0;
		}; 


		// Base class inline impemantations.
		void IRenderer2D::Push(const maths::Mat4x4& mat, bool over)
		{
			if (over)
				m_transformationStack.push_back(mat);
			else
				// In order tranform the child along with the parent we do this.
				m_transformationStack.push_back(*m_transformationBack * mat);
		}

		void IRenderer2D::Pop()
		{
			if (m_transformationStack.size() > 1)
				m_transformationStack.pop_back();
		}

	/*	class Renderer2D : public IRenderer2D
		{
		private:
			std::deque<const StaticSprite*> m_RenderQueue;
		public:
			void Submit(const IRenderable2D* renderable)  override;
			void Flush() override;
		};*/

		//class BatchRenderer2D : public IRenderer2D
		//{
		//private:
		//	GLuint m_VAO;
		//	GLuint m_VBO; 
		//	VertexData* m_buffer;
		//	IndexBuffer* m_IBO;
		//	GLsizei m_indexCount;

		//public:
		//	BatchRenderer2D();
		//	~BatchRenderer2D();

		//	void Begin() override;
		//	void Submit(const IRenderable2D* renderable)  override;
		//	void End() override;
		//	void Flush() override;
		//private:
		//	void Init();
		//};

		//// Base class inline impemantations.
		//void IRenderer2D::Push(const maths::Mat4x4& mat, bool over = false)
		//{
		//	if (over)
		//		m_transformationStack.push_back(mat);
		//	else
		//		// In order tranform the child along with the parent we do this.
		//		m_transformationStack.push_back(*m_transformationBack * mat);
		//}

		//void IRenderer2D::Pop()
		//{
		//	if(m_transformationStack.size() > 1)
		//		m_transformationStack.pop_back();
		//}
	}
}


