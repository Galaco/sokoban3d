#include "Input.h"


Input::Input(){
	mRenderWindow = nullptr;
}

Input::~Input(){
	mRenderWindow = nullptr;
}

bool Input::initialize(GLFWwindow* window){
	mRenderWindow = window;
	if(window){
		glfwSetKeyCallback(this->mRenderWindow, keyCallback);
		glfwSetMouseButtonCallback(this->mRenderWindow, mouseKeyCallback);
		glfwSetCursorPosCallback(this->mRenderWindow, cursorCallback);
		Mouse::setWindow(this->mRenderWindow);
	} else {
		this->mDebugger->log(FATAL, "Error: Input handler failed to initialise");
		return false;
	}
	this->mDebugger->log(INFO, "Input handler successfully initialised");
	return true;
}

void Input::mouseKeyCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT) Mouse::_LEFT = true; else
		if (button == GLFW_MOUSE_BUTTON_RIGHT) Mouse::_RIGHT = true;
	}
	else
	if (action == GLFW_RELEASE)
	{
		if (button == GLFW_MOUSE_BUTTON_LEFT) Mouse::_LEFT = false; else
		if (button == GLFW_MOUSE_BUTTON_RIGHT) Mouse::_RIGHT = false;
	}
}

void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		Keyboard::KEY_ESC = true;
	}
	else {
		if (key < 168)
			Keyboard::Keys[key+32] = true;
		switch(key)
		{ 
		case GLFW_KEY_UP:
			Keyboard::KEY_UP = true;
			break;
		case GLFW_KEY_DOWN:
			Keyboard::KEY_DOWN = true;
			break;
		case GLFW_KEY_LEFT:
			Keyboard::KEY_LEFT = true;
			break;
		case GLFW_KEY_RIGHT:
			Keyboard::KEY_RIGHT = true;
			break;
		}
	}
	if (action == GLFW_RELEASE) {
		if (key < 168)
			Keyboard::Keys[key + 32] = false;
		switch(key)
		{
		case GLFW_KEY_ESCAPE:
			Keyboard::KEY_ESC = false;
			break;
		case GLFW_KEY_UP:
			Keyboard::KEY_UP = false;
			break;
		case GLFW_KEY_DOWN:
			Keyboard::KEY_DOWN = false;
			break;
		case GLFW_KEY_LEFT:
			Keyboard::KEY_LEFT = false;
			break;
		case GLFW_KEY_RIGHT:
			Keyboard::KEY_RIGHT = false;
			break;
		}
	}
}

void Input::cursorCallback(GLFWwindow* window, double width, double height){
	glfwGetCursorPos(window, &Mouse::_X, &Mouse::_Y);

	// Reset mouse position for next frame

	if (Mouse::_LOCKED)
	{
		int w, h;
		glfwGetWindowSize(window, &w, &h);
		glfwSetCursorPos(window, w / 2, h / 2);
	}
}

void Input::pollEvents(){
	resetPoll();
	glfwPollEvents();
}

void Input::resetPoll(){
	if (Mouse::_LOCKED){
		Mouse::_X = Config::_WINDOWWIDTH / 2;
		Mouse::_Y = Config::_WINDOWHEIGHT / 2;
	}
}

bool Input::shutdown(){
	this->mRenderWindow = nullptr;
	return true;
}
