#include "layers.h"
#include "../textureManager.h"
#include "../renderer2d.h"
#include "../../Math/maths.h"

namespace dream {
	namespace graphics {

#pragma region Layer
		Layer::Layer(IRenderer2D* renderer, Shader * shader)
			: m_renderer(renderer), m_shader(shader)
		{
			m_shader->Enable();
			m_shader->SetUniformMat4("pr_matrix", maths::Mat4x4::Orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

			m_shader->SetUniform1iv("textures", RENDERER_MAX_TEXTURES, TextureManager::Instance().GetTextureIds());

			m_shader->Disable();
		}

		Layer::~Layer()
		{
			delete m_shader;
			delete m_renderer;
			for (size_t i = 0; i < m_renderables.size(); i++)
				delete m_renderables[i];
		}

		void Layer::Add(IRenderable2D * renderable)
		{
			m_renderables.push_back(renderable);
		}

		void Layer::Add(Group * group)
		{
			for (IRenderable2D* renderable : group->m_renderables)
				this->Add(renderable);
		}

		void Layer::Render()
		{
			m_shader->Enable();
			m_renderer->Start();

			for (size_t i = 0; i < m_renderables.size(); i++)
				m_renderables[i]->Submit(m_renderer);

			m_renderer->Stop();
			m_renderer->Flush();
		}
#pragma endregion

#pragma region TileLayer
		TileLayer::TileLayer(Shader* shader)
			: Layer(new Renderer2D(), shader)
		{

		}

		TileLayer::~TileLayer()
		{

		}
#pragma endregion		
	}
}
