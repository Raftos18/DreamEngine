#pragma once

#include "../../Interfaces/IRenderer2d.h"
#include "../../Interfaces/IRenderable2d.h"
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
			
			// This should be changed to a camera class.
			maths::Mat4x4 m_projectionMatrix;

		public:
			Layer(IRenderer2D* renderer, Shader* shader);
			virtual ~Layer();
			virtual void Add(IRenderable2D* renderable);
			virtual void Add(Group* group);
			virtual void Render();

			inline const std::vector<IRenderable2D*>& GetRenderables()  const { return m_renderables; }
		};

		// A basic Layer implementation
		class TileLayer : public Layer
		{
		public:
			TileLayer(Shader* shader);
			~TileLayer();
		};

		// A UI based layer implementation
		class UILayer : public Layer
		{
		public:
			UILayer(Shader* shader);
			~UILayer();

			void Add(IRenderable2D* renderable) override;
			void Render() override;

		private:
			// Removed from UILayer.
			void Add(Group* group) override { };
		};
	}
}



