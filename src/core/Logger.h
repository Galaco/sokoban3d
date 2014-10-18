#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <windows.h>

enum e_priority{
	_FATAL = 0,
	_ERROR,
	_WARNING,
	_INFO
};

class Logger {
public:
	Logger();
	
	~Logger();

	void log(e_priority, const char*);

private:
};

#endif
