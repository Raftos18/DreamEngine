#include "label.h"

dream::graphics::Label::Label(const std::string text, maths::Vector2 positon , GLfloat scale, unsigned int color)
	: m_Font("Fonts/arial.ttf"), m_Text(text), m_Scale(scale)
{
	m_Position = positon;
	m_Color = color;
}

void dream::graphics::Label::Submit(IRenderer2D* renderer) const
{		
	renderer->RenderText(m_Font, m_Text, m_Position.m_X, m_Position.m_Y, m_Scale, m_Color);
}
