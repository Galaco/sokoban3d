#include "Engine.h"

Input Engine::m_pInput;
GLFWwindow* Engine::m_pWindow;

Engine::Engine(){
	glfwInit();
	GLFWwindow* pWindow = glfwCreateWindow(Config::_WINDOWWIDTH , Config::_WINDOWHEIGHT, "Game Engine", NULL, NULL);
	if (!pWindow) glfwTerminate();
	glfwMakeContextCurrent(pWindow);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);

	//glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (err != GLEW_OK) {
		fprintf(stderr, "GLEW Error: %s\n", glewGetErrorString(err));
		exit(1); 
	}

	m_pWindow = pWindow;
}

Engine::~Engine(){

	glfwSetWindowShouldClose(m_pWindow, GL_TRUE);
	glfwDestroyWindow(m_pWindow);
	m_pWindow = nullptr;
}

bool Engine::initialize(){
	m_pLogger->log(_INFO, "Engine start");

	if (m_config.load()){
	    m_pLogger->log(_INFO, "Configuration: Loaded data/core/base.cfg");
	    glfwSetWindowSize(m_pWindow, Config::_WINDOWWIDTH, Config::_WINDOWHEIGHT);
		glViewport(0, 0, Config::_WINDOWWIDTH, Config::_WINDOWHEIGHT);
	} else {
	    m_pLogger->log(_WARNING, "Configuration: Failed to load 'data/core/base.cfg'. Using defaults.");
	}

	if(glfwWindowShouldClose(m_pWindow)) return false;
	m_pInput.initialize(m_pWindow);

	glClearColor(0.f, 0.f, 0.f, 0.0f);
	glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
	m_pLogger->log(_INFO, "Finished engine initialisations\n");
	return true;
}

void Engine::update(){
	m_pInput.pollEvents();
}

GLFWwindow* Engine::getCurrentContext(){
	return m_pWindow;
}