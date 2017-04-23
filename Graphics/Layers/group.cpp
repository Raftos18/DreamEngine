#include "group.h"

dream::graphics::Group::Group(maths::Mat4x4& tranform):
	m_transformationMatrix(tranform)
{

}

dream::graphics::Group::~Group()
{
	for (size_t i = 0; i < m_renderables.size(); i++)	
		delete m_renderables[i];	
}

void dream::graphics::Group::Submit(IRenderer2D * renderer) const
{
	renderer->Push(m_transformationMatrix, false);

	for (const IRenderable2D* renderable : m_renderables)
		renderable->Submit(renderer);

	renderer->Pop();
}

void dream::graphics::Group::Add(IRenderable2D * renderable)
{
	m_renderables.push_back(renderable);
}
