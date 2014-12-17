#include "Mouse.h"

bool Mouse::_VISIBILITY = false;
bool Mouse::_LOCKED = true;
bool Mouse::_LEFT = false;
bool Mouse::_RIGHT = false;
double Mouse::_X = 0;
double Mouse::_Y = 0;
GLFWwindow* Mouse::m_pWindow;

Mouse::Mouse()
{

}
Mouse::~Mouse()
{
	m_pWindow = nullptr;
}

void Mouse::show()
{
	_VISIBILITY = true;
	glfwSetInputMode(m_pWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}
void Mouse::hide()
{
	_VISIBILITY = false;
	glfwSetInputMode(m_pWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

void Mouse::lock()
{
	_LOCKED = true;
}
void Mouse::unlock()
{
	_LOCKED = false;
}


void Mouse::setWindow(GLFWwindow* pWindow)
{
	m_pWindow = pWindow;
}