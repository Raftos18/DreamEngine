#include "layers.h"
#include "../renderer2d.h"
#include "../textRenderer.h"
#include "..\..\Math\maths.h"

namespace dream {
	namespace graphics {

#pragma region Layer
		Layer::Layer(IRenderer2D* renderer, Shader * shader)
			: m_renderer(renderer), m_shader(shader)
		{			
			m_shader->Enable();			
			m_shader->SetUniformMat4("pr_matrix", maths::Mat4x4::Orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

			GLint texIDs[] = {
				0,	1,	2,	3,	4,	5,	6,	7,	8,	9,
				10,	11,	12,	13,	14,	15,	16,	17,	18,	19,
				20,	21,	22,	23,	24,	25,	26,	27,	28,	29,
				30, 31
			};
			m_shader->SetUniform1iv("textures", 32, texIDs);

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
			m_renderer->Begin();

			for (size_t i = 0; i < m_renderables.size(); i++)
				m_renderables[i]->Submit(m_renderer);

			m_renderer->End();
			m_renderer->Flush();					
		}
#pragma endregion
	
#pragma region TileLayer
		TileLayer::TileLayer(Shader* shader)
			: Layer(new BatchRenderer2D(), shader)
		{

		}

		TileLayer::~TileLayer()
		{

		}
#pragma endregion		

#pragma region UILayer		
		UILayer::UILayer(Shader * shader)
			: Layer(new TextRenderer(), shader)
		{

		}

		UILayer::~UILayer()
		{

		}

		void UILayer::Add(IRenderable2D * renderable)
		{
			if (dynamic_cast<Label*>(renderable))
				m_renderables.push_back(renderable);
		}

		void UILayer::Render()
		{
			m_shader->Enable();			
			for (size_t i = 0; i < m_renderables.size(); i++)
			{		
				// I want something like that but as long as Color is an unsigned int it is not possible
				//m_shader->SetUniform3f("textColor", m_renderables[i]->m_Color);
				m_renderables[i]->Submit(m_renderer);
			}
		}
#pragma endregion		
	}
}

