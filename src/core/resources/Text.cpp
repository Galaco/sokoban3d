#include "Text.h"

Texture* Text::texture = nullptr;

Text::Text(const char* string, double height){
	m_color = glm::vec3(1.f, 1.f, 1.f);
	m_height = height;	//12 is default height. Screenspace transaltes to 7.5% of total screen height;
	m_string = string;
}

Text::~Text(){
}

void Text::setColor(glm::vec3 color)
{
	m_color = color;
}
glm::vec3& Text::getColor()
{
	return m_color;
}

double Text::getScaleScreenSpace()
{
	return m_height / 80.f;
}
double Text::getScale()
{
	return m_height;
}

std::string& Text::getString()
{
	return m_string;
}