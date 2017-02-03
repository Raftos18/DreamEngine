#pragma once

#include "renderer2d.h"
#include "renderable2d.h"
#include "group.h"

namespace dream
{
	namespace graphics
	{
		class Layer
		{
		protected:
			IRenderer2D* m_renderer;
			std::vector<IRenderable2D*> m_renderables;
			Shader* m_shader;
			
			Mat4x4 m_projectionMatrix;

			Layer(IRenderer2D* renderer, Shader* shader);

		public:
			virtual ~Layer();
			virtual void Add(IRenderable2D* renderable);
			virtual void Add(Group* group);
			virtual void Render();
		};


		class TileLayer : public Layer
		{
		public:
			TileLayer(Shader* shader);
			~TileLayer();
		};
	}
}



