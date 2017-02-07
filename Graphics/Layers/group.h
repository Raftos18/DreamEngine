#pragma once
#include "renderable2d.h"

namespace dream
{
	namespace graphics
	{
		class Group : public IRenderable2D
		{
		public:
			std::vector<IRenderable2D*> m_renderables;
			maths::Mat4x4 m_transformationMatrix;
		public:
			Group(maths::Mat4x4& tranform);
			void Submit(IRenderer2D* renderer) const override; 

			void Add(IRenderable2D* renderable);
		};
	}
}



