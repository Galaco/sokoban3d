/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Mouse
Description: Stores mouse information
*********************************************************************/
#ifndef MOUSE_H
#define MOUSE_H

#include <GLFW/glfw3.h>

class Mouse {
public:
	Mouse();
	~Mouse();

	static bool _VISIBILITY;
	static bool _LOCKED;

	static void show();
	static void hide();

	static void lock();
	static void unlock();

	static double _X;
	static double _Y;

	static bool _LEFT;
	static bool _RIGHT;

	static void setWindow(GLFWwindow*);
private:
	static GLFWwindow* m_pWindow;

};
#endif
