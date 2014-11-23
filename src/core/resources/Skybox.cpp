#include "Skybox.h"

Skybox::Skybox() {
	m_vbo = 0;
	zFar = 128.f;
}

Skybox::~Skybox(){
}

void Skybox::load(std::string a_sDirectory) {
	loadTexture((a_sDirectory+"_ft.jpg").c_str(), 0); 
	loadTexture((a_sDirectory+"_bk.jpg").c_str(), 1); 
	loadTexture((a_sDirectory+"_lf.jpg").c_str(), 2); 
	loadTexture((a_sDirectory+"_rt.jpg").c_str(), 3); 
	loadTexture((a_sDirectory+"_up.jpg").c_str(), 4); 
	loadTexture((a_sDirectory+"_dn.jpg").c_str(), 5); 
}

void Skybox::loadTexture(const char* path, int i){
	sf::Image image;
	std::string str(path);
	if(!image.loadFromFile( path )) {
		str =  "Skybox: Failed to load texture: "+ str;
		m_pLogger->log(ERROR_, str.c_str());
		return;
	} else {
		str =  "Skybox: Loaded texture: "+ str;
		m_pLogger->log(SUCCESS, str.c_str());
	}

	// allocate a texture name
	glGenTextures( 1 , &mTexture[i] );
	glBindTexture( GL_TEXTURE_2D , mTexture[i] );
	sampler_state[i] = 0;

	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB, image.getSize().x , image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr() );

	glGenSamplers(1, &sampler_state[i]);
	glSamplerParameteri(sampler_state[i], GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
	glSamplerParameteri(sampler_state[i], GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glSamplerParameteri(sampler_state[i], GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glSamplerParameteri(sampler_state[i], GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void Skybox::createCube(){
	float size = sqrt(std::pow(zFar*0.82f, 2)/2);

	glm::vec3 vSkyBoxVertices[24] = 
	{
		// Front face
		glm::vec3(size, size, size), glm::vec3(size, -size, size), glm::vec3(-size, size, size), glm::vec3(-size, -size, size),
		// Back face
		glm::vec3(-size, size, -size), glm::vec3(-size, -size, -size), glm::vec3(size, size, -size), glm::vec3(size, -size, -size),
		// Left face
		glm::vec3(-size, size, size), glm::vec3(-size, -size, size), glm::vec3(-size, size, -size), glm::vec3(-size, -size, -size),
		// Right face
		glm::vec3(size, size, -size), glm::vec3(size, -size, -size), glm::vec3(size, size, size), glm::vec3(size, -size, size),
		// Top face
		glm::vec3(-size, size, -size), glm::vec3(size, size, -size), glm::vec3(-size, size, size), glm::vec3(size, size, size),
		// Bottom face
		glm::vec3(size, -size, -size), glm::vec3(-size, -size, -size), glm::vec3(size, -size, size), glm::vec3(-size, -size, size),
	};
	glm::vec2 vSkyBoxTexCoords[4] =
	{
		glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 1.0f), glm::vec2(1.0f, 0.0f), glm::vec2(1.0f, 1.0f)
	};

	glm::vec3 vSkyBoxNormals[6] = 
	{
		glm::vec3(0.0f, 0.0f, -1.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(1.0f, 0.0f, 0.0f),
		glm::vec3(-1.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, -1.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	};
	for(int i=0; i<24; ++i) {
		vertices.push_back(vSkyBoxVertices[i]);
		uvs.push_back(vSkyBoxTexCoords[i%4]);
		normals.push_back(vSkyBoxNormals[i/4]);
	}

	glGenVertexArrays(1, &m_vao); 
	glBindVertexArray(m_vao); 

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0] , GL_STATIC_DRAW);

	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, uvs.size() * sizeof(glm::vec2), &uvs[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);


	// Vertex positions
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
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
	glBindBuffer(GL_ARRAY_BUFFER,uvBuffer);
	glVertexAttribPointer(
		1,                                // attribute
		2,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	// 3rd attribute buffer : normals
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glVertexAttribPointer(
		2,                                // attribute
		3,                                // size
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);

	glBindVertexArray(0);
}

GLuint& Skybox::getVbo(){
	return m_vbo;
}
GLuint& Skybox::getVao(){
	return m_vao;
}
GLuint& Skybox::getTexture(){
	return m_vbo;
}
void Skybox::bindTexture(int i){
	glBindTexture( GL_TEXTURE_2D , mTexture[i] );
}
void Skybox::bindSampler(int i){
	glBindSampler(0, sampler_state[i]);
}
void Skybox::setzFar(float dist){
	zFar = dist;
}