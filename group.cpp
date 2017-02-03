#include "group.h"

dream::graphics::Group::Group(maths::Mat4x4& tranform):
	m_transformationMatrix(tranform)
{

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
