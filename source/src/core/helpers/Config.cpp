#include "Config.h"

unsigned int Config::_DEBUGLEVEL = 0;
unsigned int Config::_WINDOWWIDTH = 800;
unsigned int Config::_WINDOWHEIGHT = 480;
bool	     Config::_FULLSCREEN = false;
unsigned int Config::_ANTIALIASING = 0;
bool	     Config::_VSYNC = false;
float        Config::_MASTER_VOL = 1.0;
float        Config::_SENSITIVITY = 1.0;
    

Config::Config(){
}

Config::~Config(){

}


void Config::map(std::map<std::string, std::string> m) {
	// Maps the loaded data onto config settings
	_DEBUGLEVEL = atoi(m["debug"].c_str());
	_SENSITIVITY = (atoi(m["sensitivity"].c_str()))/1000.f;
	//visuals
	_WINDOWWIDTH = atoi(m["width"].c_str());
    _WINDOWHEIGHT = atoi(m["height"].c_str());
    _FULLSCREEN = (atoi(m["fullscreen"].c_str())) != 0;
    _ANTIALIASING = atoi(m["antialiasing"].c_str());
    _VSYNC = (atoi(m["vsync"].c_str())) != 0;

    //audio
    _MASTER_VOL = (float)atof(m["master_volume"].c_str());
}

bool Config::load() {
	//Loads config data from the config file. Location not setable.
    std::map<std::string, std::string> m;
    std::ifstream f;
    std::string d, holder;
    f.open( "config/default.cfg" );
    if( f.is_open() )
    {
	while( f >> holder )
	{
            if( ( holder == "#" ) || ( holder == "g" ) ) {
		getline(f , d , '\n' );
	    } else {
		f >> d;
		m[holder] = d;
	    }
	}
	f.close();
    } else {
	return false;
    }
    map(m);
    
    return true;
}

void Config::write()
{
	//@TODO: Write current config back to config file
}