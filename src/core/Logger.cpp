#include "Logger.h"
	
Logger::~Logger(){

}

Logger::Logger(){

}

void Logger::log(e_priority priority, const char* msg){
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	switch(priority) {
	case _FATAL:
			MessageBoxA(NULL, msg, "A fatal error has occurred", MB_OK);
			exit(0);
		break;
	case _ERROR:
		SetConsoleTextAttribute(hConsole, 4);
		std::cout << msg << "\n";
		break;
	case _WARNING:
		SetConsoleTextAttribute(hConsole, 14);
		std::cout << msg << "\n";
		break;
	case _INFO:
		SetConsoleTextAttribute(hConsole, 15);
		std::cout << msg << "\n";
		break;
	default:
		std::cout << msg << "\n";
		break;
	}
}