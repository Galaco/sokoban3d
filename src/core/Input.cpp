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
		glfwSetCursorPosCallback(this->mRenderWindow, cursorCallback);
		Mouse::setWindow(this->mRenderWindow);
	} else {
		this->mDebugger->log(FATAL, "Error: Input handler failed to initialise");
		return false;
	}
	this->mDebugger->log(INFO, "Input handler successfully initialised");
	return true;
}

void Input::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		Keyboard::KEY_ESC = true;
	} else {
		switch(key)
		{
		case GLFW_KEY_1:
			Keyboard::KEY_1 = true;
			break;
		case GLFW_KEY_2:
			Keyboard::KEY_2 = true;
			break;
		case GLFW_KEY_3:
			Keyboard::KEY_3 = true;
			break;
		case GLFW_KEY_4:
			Keyboard::KEY_4 = true;
			break;
		case GLFW_KEY_5:
			Keyboard::KEY_5 = true;
			break;
		case GLFW_KEY_6:
			Keyboard::KEY_6 = true;
			break;
		case GLFW_KEY_7:
			Keyboard::KEY_7 = true;
			break;
		case GLFW_KEY_8:
			Keyboard::KEY_8 = true;
			break;
		case GLFW_KEY_9:
			Keyboard::KEY_9 = true;
			break;
		case GLFW_KEY_0:
			Keyboard::KEY_0 = true;
			break;
		case GLFW_KEY_Q:
			Keyboard::KEY_Q = true;
			break;
		case GLFW_KEY_W:
			Keyboard::KEY_W = true;
			break;
		case GLFW_KEY_E:
			Keyboard::KEY_E = true;
			break;
		case GLFW_KEY_R:
			Keyboard::KEY_R = true;
			break;
		case GLFW_KEY_T:
			Keyboard::KEY_T = true;
			break;
		case GLFW_KEY_Y:
			Keyboard::KEY_Y = true;
			break;
		case GLFW_KEY_U:
			Keyboard::KEY_U = true;
			break;
		case GLFW_KEY_I:
			Keyboard::KEY_I = true;
			break;
		case GLFW_KEY_O:
			Keyboard::KEY_O = true;
			break;
		case GLFW_KEY_P:
			Keyboard::KEY_P = true;
			break;
		case GLFW_KEY_A:
			Keyboard::KEY_A = true;
			break;
		case GLFW_KEY_S:
			Keyboard::KEY_S = true;
			break;
		case GLFW_KEY_D:
			Keyboard::KEY_D = true;
			break;
		case GLFW_KEY_F:
			Keyboard::KEY_F = true;
			break;
		case GLFW_KEY_G:
			Keyboard::KEY_G = true;
			break;
		case GLFW_KEY_H:
			Keyboard::KEY_H = true;
			break;
		case GLFW_KEY_J:
			Keyboard::KEY_J = true;
			break;
		case GLFW_KEY_K:
			Keyboard::KEY_K = true;
			break;
		case GLFW_KEY_L:
			Keyboard::KEY_L = true;
			break;
		case GLFW_KEY_Z:
			Keyboard::KEY_Z = true;
			break;
		case GLFW_KEY_X:
			Keyboard::KEY_X = true;
			break;
		case GLFW_KEY_C:
			Keyboard::KEY_C = true;
			break;
		case GLFW_KEY_V:
			Keyboard::KEY_V = true;
			break;
		case GLFW_KEY_B:
			Keyboard::KEY_B = true;
			break;
		case GLFW_KEY_N:
			Keyboard::KEY_N = true;
			break;
		case GLFW_KEY_M:
			Keyboard::KEY_M = true;
			break; 
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
		case GLFW_MOUSE_BUTTON_LEFT:
			Mouse::_LEFT = true;
			break;
		case GLFW_MOUSE_BUTTON_RIGHT:
			Mouse::_RIGHT = true;
			break;
		}
	}
	if (action == GLFW_RELEASE) {
		switch(key)
		{
		case GLFW_KEY_1:
			Keyboard::KEY_1 = false;
			break;
		case GLFW_KEY_2:
			Keyboard::KEY_2 = false;
			break;
		case GLFW_KEY_3:
			Keyboard::KEY_3 = false;
			break;
		case GLFW_KEY_4:
			Keyboard::KEY_4 = false;
			break;
		case GLFW_KEY_5:
			Keyboard::KEY_5 = false;
			break;
		case GLFW_KEY_6:
			Keyboard::KEY_6 = false;
			break;
		case GLFW_KEY_7:
			Keyboard::KEY_7 = false;
			break;
		case GLFW_KEY_8:
			Keyboard::KEY_8 = false;
			break;
		case GLFW_KEY_9:
			Keyboard::KEY_9 = false;
			break;
		case GLFW_KEY_0:
			Keyboard::KEY_0 = false;
			break;
		case GLFW_KEY_Q:
			Keyboard::KEY_Q = false;
			break;
		case GLFW_KEY_W:
			Keyboard::KEY_W = false;
			break;
		case GLFW_KEY_E:
			Keyboard::KEY_E = false;
			break;
		case GLFW_KEY_R:
			Keyboard::KEY_R = false;
			break;
		case GLFW_KEY_T:
			Keyboard::KEY_T = false;
			break;
		case GLFW_KEY_Y:
			Keyboard::KEY_Y = false;
			break;
		case GLFW_KEY_U:
			Keyboard::KEY_U = false;
			break;
		case GLFW_KEY_I:
			Keyboard::KEY_I = false;
			break;
		case GLFW_KEY_O:
			Keyboard::KEY_O = false;
			break;
		case GLFW_KEY_P:
			Keyboard::KEY_P = false;
			break;
		case GLFW_KEY_A:
			Keyboard::KEY_A = false;
			break;
		case GLFW_KEY_S:
			Keyboard::KEY_S = false;
			break;
		case GLFW_KEY_D:
			Keyboard::KEY_D = false;
			break;
		case GLFW_KEY_F:
			Keyboard::KEY_F = false;
			break;
		case GLFW_KEY_G:
			Keyboard::KEY_G = false;
			break;
		case GLFW_KEY_H:
			Keyboard::KEY_H = false;
			break;
		case GLFW_KEY_J:
			Keyboard::KEY_J = false;
			break;
		case GLFW_KEY_K:
			Keyboard::KEY_K = false;
			break;
		case GLFW_KEY_L:
			Keyboard::KEY_L = false;
			break;
		case GLFW_KEY_Z:
			Keyboard::KEY_Z = false;
			break;
		case GLFW_KEY_X:
			Keyboard::KEY_X = false;
			break;
		case GLFW_KEY_C:
			Keyboard::KEY_C = false;
			break;
		case GLFW_KEY_V:
			Keyboard::KEY_V = false;
			break;
		case GLFW_KEY_B:
			Keyboard::KEY_B = false;
			break;
		case GLFW_KEY_N:
			Keyboard::KEY_N = false;
			break;
		case GLFW_KEY_M:
			Keyboard::KEY_M = false;
			break;
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
		case GLFW_MOUSE_BUTTON_LEFT:
			Mouse::_LEFT = false;
			break;
		case GLFW_MOUSE_BUTTON_RIGHT:
			Mouse::_RIGHT = false;
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
