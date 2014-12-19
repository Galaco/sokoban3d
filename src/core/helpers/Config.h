/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Configuration
Description: Stores global configurations loaded. Has defaults,
			 can be overridden by successful fileload and parse
*********************************************************************/
#ifndef CONFIG_H
#define CONFIG_H

#include <map>
#include <string>
#include <fstream>

class Config
{
public:
    Config();
    ~Config();
    void map(std::map<std::string, std::string>);
    bool load();

	void write();
        
    static unsigned int _DEBUGLEVEL, _WINDOWWIDTH, _WINDOWHEIGHT;
    static bool	        _FULLSCREEN;
    static unsigned int _ANTIALIASING;
    static bool	        _VSYNC;
    
    static float          _MASTER_VOL, _SENSITIVITY;
    
private:
	
};
#endif
