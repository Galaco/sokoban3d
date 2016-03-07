#include "Text.h"

Texture* Text::texture = nullptr;

Text::Text(const char* string, double height, Model * model){
	m_color = glm::vec3(1.f, 1.f, 1.f);
	m_height = height;	//12 is default height. Screenspace transaltes to 7.5% of total screen height;
	m_string = string;

	generate(model);
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


void Text::generate(Model* model)
{
	Mesh m;

	std::vector<glm::vec3> Positions;
	std::vector<glm::vec3> Normals;
	std::vector<glm::vec2> TexCoords;
	std::vector<VertexBoneData> Bones;
	std::vector<GLuint> Indices;

	for (unsigned int i = 0; i < m_string.length(); i++){
		glm::vec3 vertex_up_left = glm::vec3((i*m_height / 2) / 120, m_height / 120, 0);
		glm::vec3 vertex_up_right = glm::vec3((i*m_height / 2 + m_height / 2) / 120, m_height / 120, 0);
		glm::vec3 vertex_down_right = glm::vec3((i*m_height / 2 + m_height / 2) / 120, 0, 0);
		glm::vec3 vertex_down_left = glm::vec3((i*m_height / 2) / 120, 0, 0);

		Positions.push_back(vertex_up_left);
		Positions.push_back(vertex_down_left);
		Positions.push_back(vertex_up_right);

		Positions.push_back(vertex_down_right);
		Positions.push_back(vertex_up_right);
		Positions.push_back(vertex_down_left);
		

		char character = m_string[i];
		float uv_x = ((character % 16) / 16.0f);
		float uv_y = ((character / 16) / 16.0f);


		glm::vec2 uv_up_left = glm::vec2(uv_x + (1/32), uv_y);
		glm::vec2 uv_up_right = glm::vec2(uv_x + 1.0f / 16.0f - (1 / 32), uv_y);
		glm::vec2 uv_down_right = glm::vec2(uv_x + 1.0f / 16.0f - (1 / 32), (uv_y + 1.0f / 16.0f));
		glm::vec2 uv_down_left = glm::vec2(uv_x + (1 / 32), (uv_y + 1.0f / 16.0f));

		TexCoords.push_back(uv_up_left);
		TexCoords.push_back(uv_down_left);
		TexCoords.push_back(uv_up_right);

		TexCoords.push_back(uv_down_right);
		TexCoords.push_back(uv_up_right);
		TexCoords.push_back(uv_down_left);
	}

	MeshEntry entry;
	entry.NumIndices = Positions.size();

	m.m_Entries.push_back(entry);

	//Gen mesh info
	glGenVertexArrays(1, &m.m_VAO);
	glBindVertexArray(m.m_VAO);

	glGenBuffers(1, &m.m_Buffers[POS_VB]);
	glBindBuffer(GL_ARRAY_BUFFER, m.m_Buffers[POS_VB]);
	glBufferData(GL_ARRAY_BUFFER, Positions.size() * sizeof(glm::vec3), &Positions[0], GL_STATIC_DRAW);

	glGenBuffers(1, &m.m_Buffers[TEXCOORD_VB]);
	glBindBuffer(GL_ARRAY_BUFFER, m.m_Buffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, TexCoords.size() * sizeof(glm::vec2), &TexCoords[0], GL_STATIC_DRAW);

	// Vertex positions
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m.m_Buffers[POS_VB]);
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
	glBindBuffer(GL_ARRAY_BUFFER, m.m_Buffers[TEXCOORD_VB]);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
		);

	glBindVertexArray(0);

	if (model) {
		model->addMesh(m);
	}
	else {
		m_model.addMesh(m);
	}
}