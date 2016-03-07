#include "Logger.h"

std::fstream Logger::m_file;
	
Logger::~Logger(){
	m_file.close();
}

Logger::Logger(){

}

void Logger::log(e_priority priority, const char* msg){
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	switch(priority) {
	case FATAL:
			MessageBoxA(NULL, msg, "A fatal error has occurred", MB_OK);
			exit(0);
		break;
	case ERROR_:
		SetConsoleTextAttribute(hConsole, 4);
		std::cout << msg << "\n";
		SetConsoleTextAttribute(hConsole, 15);
		break;
	case WARNING:
		SetConsoleTextAttribute(hConsole, 14);
		std::cout << msg << "\n";
		SetConsoleTextAttribute(hConsole, 15);
		break;
	case INFO:
		std::cout << msg << "\n";
		break;
	case SUCCESS:
		SetConsoleTextAttribute(hConsole, 10);
		std::cout << msg << "\n";
		SetConsoleTextAttribute(hConsole, 15);
		break;
	default:
		std::cout << msg << "\n";
		break;
	}
}


//Log to file
void Logger::write(const char* msg){
	if (Config::_DEBUGLEVEL > 0)
	{
		m_file.open("test.txt", std::fstream::in | std::fstream::out | std::fstream::app);

		m_file << msg << "\n";
	}

}