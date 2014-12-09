#include "Text.h"

Texture* Text::texture = nullptr;

Text::Text(const char* string, double height){
	m_color = glm::vec3(1.f, 1.f, 1.f);
	m_height = height;	//12 is default height. Screenspace transaltes to 7.5% of total screen height;
	m_string = string;

	generate();
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

Model& Text::getModel()
{
	return m_model;
}


void Text::generate()
{
	Mesh m;
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> UVs;

	for (unsigned int i = 0; i < m_string.length(); i++){
		glm::vec3 vertex_up_left = glm::vec3(i*m_height, m_height, 0);
		glm::vec3 vertex_up_right = glm::vec3(i*m_height + m_height, m_height, 0);
		glm::vec3 vertex_down_right = glm::vec3(i*m_height + m_height, 0, 0);
		glm::vec3 vertex_down_left = glm::vec3(i*m_height, 0, 0);

		vertices.push_back(vertex_up_left);
		vertices.push_back(vertex_down_left);
		vertices.push_back(vertex_up_right);

		vertices.push_back(vertex_down_right);
		vertices.push_back(vertex_up_right);
		vertices.push_back(vertex_down_left);
		

		char character = m_string[i];
		float uv_x = (character % 16) / 16.0f;
		float uv_y = ((character / 16) / 16.0f);


		glm::vec2 uv_up_left = glm::vec2(uv_x, uv_y);// (1.0f - uv_y);
		glm::vec2 uv_up_right = glm::vec2(uv_x + 1.0f / 16.0f, uv_y);// 1.0f - uv_y);
		glm::vec2 uv_down_right = glm::vec2(uv_x + 1.0f / 16.0f, (uv_y + 1.0f / 16.0f));
		glm::vec2 uv_down_left = glm::vec2(uv_x, (uv_y + 1.0f / 16.0f));

		UVs.push_back(uv_up_left);
		UVs.push_back(uv_down_left);
		UVs.push_back(uv_up_right);

		UVs.push_back(uv_down_right);
		UVs.push_back(uv_up_right);
		UVs.push_back(uv_down_left);
	}

	m.m_vertexCount = vertices.size();

	//Gen mesh info
	glGenVertexArrays(1, &m.uiVAO);
	glBindVertexArray(m.uiVAO);

	glGenBuffers(1, &m.uiBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m.uiBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &m.uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m.uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, UVs.size() * sizeof(glm::vec2), &UVs[0], GL_STATIC_DRAW);

	// Vertex positions
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m.uiBuffer);
	glVertexAttribPointer(
		0,                  // attribute
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
		);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m.uvBuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
		);

	glBindVertexArray(0);

	m_model.addMesh(m);
}