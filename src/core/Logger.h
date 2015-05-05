/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Logger
Description: Low level logging class. Outputs to console with 
			 varying levels of importance.
*********************************************************************/
#ifndef LOGGER_H
#define LOGGER_H

#include <windows.h>
#include <iostream>
#include <fstream>
#include <core/helpers/Config.h>

enum e_priority{
	FATAL = 0,
	ERROR_,
	WARNING,
	INFO,
	SUCCESS
};

class Logger {
public:
	Logger();
	
	~Logger();

	static void log(e_priority priority, const char* msg);	// Log a message onto the console

	static void write(const char* msg);	//Write a message to the debug file

private:
	static std::fstream m_file;
};

#endif
