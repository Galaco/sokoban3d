#include "Engine.h"

Input Engine::m_pInput;
GLFWwindow* Engine::m_pWindow;

Engine::Engine(){
	glfwInit();

	GLFWwindow* pWindow = nullptr;

	if (m_config.load()){
		Logger::log(SUCCESS, "Configuration: Loaded data/core/base.cfg");
		if (Config::_FULLSCREEN) {
			pWindow = glfwCreateWindow(Config::_WINDOWWIDTH, Config::_WINDOWHEIGHT, "Sokoban 3D", glfwGetPrimaryMonitor(), NULL);
		} else {
			pWindow = glfwCreateWindow(Config::_WINDOWWIDTH, Config::_WINDOWHEIGHT, "Sokoban 3D", NULL, NULL);
		}
	}
	else {
		Logger::log(WARNING, "Configuration: Failed to load 'data/core/base.cfg'. Using defaults.");
		pWindow = glfwCreateWindow(Config::_WINDOWWIDTH, Config::_WINDOWHEIGHT, "Sokoban 3D", NULL, NULL);
	}
	
	if (!pWindow) glfwTerminate();
	glfwMakeContextCurrent(pWindow);


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, FALSE);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, TRUE);
	glViewport(0, 0, Config::_WINDOWWIDTH, Config::_WINDOWHEIGHT);
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
	Logger::log(INFO, "Engine start");

	if(glfwWindowShouldClose(m_pWindow)) return false;
	m_pInput.initialize(m_pWindow);

	Logger::log(INFO, "Finished engine initialisations\n");

	glfwSetInputMode(m_pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	return true;
}

void Engine::update(){
	m_pInput.pollEvents();
}

GLFWwindow* Engine::getCurrentContext(){
	return m_pWindow;
}