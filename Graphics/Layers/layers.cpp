#include "layers.h"
#include "..\batchRenderer.h"
#include "..\..\Math\maths.h"

dream::graphics::Layer::Layer(IRenderer2D* renderer, Shader * shader)
	: m_renderer(renderer), m_shader(shader)
{
	m_shader->Enable();
	m_shader->SetUniformMat4("pr_matrix", Mat4x4::Orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));
	m_shader->Disable();
}


dream::graphics::Layer::~Layer()
{
	delete m_shader;
	delete m_renderer;
	for (size_t i = 0; i < m_renderables.size(); i++)
		delete m_renderables[i];
	
}

void dream::graphics::Layer::Add(IRenderable2D * renderable)
{
	m_renderables.push_back(renderable);
}

void dream::graphics::Layer::Add(Group * group)
{
	for (IRenderable2D* renderable : group->m_renderables)
		this->Add(renderable);
}

void dream::graphics::Layer::Render()
{
	m_shader->Enable();
	m_renderer->Begin();

	for (size_t i = 0; i < m_renderables.size(); i++)
		m_renderables[i]->Submit(m_renderer);
		
	m_renderer->End();
	m_renderer->Flush();

	//m_shader->Disable();
}



dream::graphics::TileLayer::TileLayer(Shader* shader)
	: Layer(new BatchRenderer2D(), shader)
{

}

dream::graphics::TileLayer::~TileLayer()
{

}
