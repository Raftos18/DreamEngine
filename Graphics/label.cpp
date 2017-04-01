#include "label.h"

dream::graphics::Label::Label(const std::string text, maths::Vector2 positon , GLfloat scale, maths::Vector3 color)
	: m_Text(text), m_Scale(scale), Color(color)
{
	m_Position = positon;
}

void dream::graphics::Label::Submit(IRenderer2D* renderer) const
{	
	maths::Vector3 c = Color;
	renderer->RenderText(m_Text, m_Position.m_X, m_Position.m_Y, m_Scale, c);
}
