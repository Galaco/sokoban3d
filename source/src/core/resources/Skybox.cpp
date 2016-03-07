#include "Skybox.h"

bool Skybox::shaderReady = false;

Skybox::Skybox() {
	zFar = 128.f;
	vao = -1;
	if (!shaderReady)
	{
		createShader();
	}
}

Skybox::~Skybox(){
}

void Skybox::load(std::string a_sDirectory) {
	a_sDirectory = "assets/materials/" + a_sDirectory;

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);

	loadTexture((a_sDirectory + "_bk.png").c_str(), GL_TEXTURE_CUBE_MAP_NEGATIVE_Z);
	loadTexture((a_sDirectory + "_ft.png").c_str(), GL_TEXTURE_CUBE_MAP_POSITIVE_Z);
	loadTexture((a_sDirectory + "_up.png").c_str(), GL_TEXTURE_CUBE_MAP_POSITIVE_Y);
	loadTexture((a_sDirectory + "_dn.png").c_str(), GL_TEXTURE_CUBE_MAP_NEGATIVE_Y);
	loadTexture((a_sDirectory + "_rt.png").c_str(), GL_TEXTURE_CUBE_MAP_NEGATIVE_X);
	loadTexture((a_sDirectory + "_lf.png").c_str(), GL_TEXTURE_CUBE_MAP_POSITIVE_X);


	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void Skybox::loadTexture(const char* path, GLenum side){
	sf::Image image;
	std::string str(path);
	if(!image.loadFromFile( path )) {
		str =  "Skybox: Failed to load texture: "+ str;
		Logger::log(ERROR_, str.c_str());
		return;
	} else {
		str =  "Skybox: Loaded texture: "+ str;
		Logger::log(SUCCESS, str.c_str());
	}

	glTexImage2D( side, 0, GL_RGB, image.getSize().x , image.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr() );
}

void Skybox::createCube(){
	float size = sqrt(std::pow(zFar*0.75f, 2)/2);

	float points[] = {
		-size, size, -size,
		-size, -size, -size,
		size, -size, -size,
		size, -size, -size,
		size, size, -size,
		-size, size, -size,

		-size, -size, size,
		-size, -size, -size,
		-size, size, -size,
		-size, size, -size,
		-size, size, size,
		-size, -size, size,

		size, -size, -size,
		size, -size, size,
		size, size, size,
		size, size, size,
		size, size, -size,
		size, -size, -size,

		-size, -size, size,
		-size, size, size,
		size, size, size,
		size, size, size,
		size, -size, size,
		-size, -size, size,

		-size, size, -size,
		size, size, -size,
		size, size, size,
		size, size, size,
		-size, size, size,
		-size, size, -size,

		-size, -size, -size,
		-size, -size, size,
		size, -size, -size,
		size, -size, -size,
		-size, -size, size,
		size, -size, size
	};

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 108 * sizeof(float), &points, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glBindVertexArray(0);

	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
}

GLuint Skybox::getVbo(){
	return vbo;
}

GLuint Skybox::getVao(){
	return vao;
}

GLuint Skybox::getTexture(){
	return m_texture;
}

void Skybox::bindTexture(){
	glBindTexture( GL_TEXTURE_CUBE_MAP , m_texture );
}

void Skybox::setzFar(float dist){
	zFar = dist;
}

void Skybox::createShader()
{
	bool vsLoad = m_shader[0].loadShader("binaries/shaders/skybox.vs.glsl", GL_VERTEX_SHADER);
	bool fsLoad = m_shader[1].loadShader("binaries/shaders/skybox.fs.glsl", GL_FRAGMENT_SHADER);

	if (!vsLoad || !fsLoad)
		Logger::log(ERROR_, "Failed to load skybox shader/s.");

	m_shaderProg.createProgram();
	m_shaderProg.addShaderToProgram(&m_shader[0]);
	m_shaderProg.addShaderToProgram(&m_shader[1]);
	m_shaderProg.linkProgram();

	shaderReady = true;
}

void Skybox::useProgram()
{
	m_shaderProg.useProgram();
	m_shaderProg.setUniform("VP", Pipeline::getWorldMatrix());
}