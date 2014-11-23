/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Input
Description: Responsible for obtaining Input data, and, where relevant
			 passing it to the Keyboard. Should always be static.
*********************************************************************/
#ifndef INPUT_H
#define INPUT_H

#include <core/Logger.h>

#include <GLFW/glfw3.h>

#include <core/helpers/Config.h>
#include <core/helpers/Keyboard.h>

class Input {
public:
	Input();

	~Input();

	void		pollEvents();
	static void keyCallback(GLFWwindow*, int, int, int, int);
	static void cursorCallback(GLFWwindow*, double, double);
	static void windowsizeCallback(GLFWwindow*, int, int);

	bool		initialize(GLFWwindow*);
	bool		shutdown();

private:
	void resetPoll();


	Config      m_config;
	Logger*		mDebugger;
	GLFWwindow*	mRenderWindow;
};
#endif
