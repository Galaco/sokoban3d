#ifndef INPUT_H
#define INPUT_H

#include <core/Logger.h>

#include <GLFW/glfw3.h>

#include <core/Config.h>
#include <core/Keyboard.h>

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
