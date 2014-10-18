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
        
    static unsigned int _WINDOWWIDTH, _WINDOWHEIGHT;
    static bool	        _FULLSCREEN;
    static unsigned int _ANTIALIASING;
    static bool	        _VSYNC;
    
    static float          _MASTER_VOL;
    
private:
	
};
#endif
