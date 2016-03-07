#include "Keyboard.h"

bool Keyboard::KEY_F1		= false;
bool Keyboard::KEY_F2		= false;
bool Keyboard::KEY_F3		= false;
bool Keyboard::KEY_F4		= false;
bool Keyboard::KEY_F5		= false;
bool Keyboard::KEY_F6		= false;
bool Keyboard::KEY_F7		= false;
bool Keyboard::KEY_F8		= false;
bool Keyboard::KEY_F9		= false;
bool Keyboard::KEY_F10		= false;
bool Keyboard::KEY_F11		= false;
bool Keyboard::KEY_F12		= false;

bool Keyboard::KEY_1		= false;
bool Keyboard::KEY_2		= false;
bool Keyboard::KEY_3		= false;
bool Keyboard::KEY_4		= false;
bool Keyboard::KEY_5		= false;
bool Keyboard::KEY_6		= false;
bool Keyboard::KEY_7		= false;
bool Keyboard::KEY_8		= false;
bool Keyboard::KEY_9		= false;
bool Keyboard::KEY_0		= false;

bool Keyboard::KEY_Q		= false;
bool Keyboard::KEY_W		= false;
bool Keyboard::KEY_E		= false;
bool Keyboard::KEY_R		= false;
bool Keyboard::KEY_T		= false;
bool Keyboard::KEY_Y		= false;
bool Keyboard::KEY_U		= false;
bool Keyboard::KEY_I		= false;
bool Keyboard::KEY_O		= false;
bool Keyboard::KEY_P		= false;

bool Keyboard::KEY_A		= false;
bool Keyboard::KEY_S		= false;
bool Keyboard::KEY_D		= false;
bool Keyboard::KEY_F		= false;
bool Keyboard::KEY_G		= false;
bool Keyboard::KEY_H		= false;
bool Keyboard::KEY_J		= false;
bool Keyboard::KEY_K		= false;
bool Keyboard::KEY_L		= false;

bool Keyboard::KEY_Z		= false;
bool Keyboard::KEY_X		= false;
bool Keyboard::KEY_C		= false;
bool Keyboard::KEY_V		= false;
bool Keyboard::KEY_B		= false;
bool Keyboard::KEY_N		= false;
bool Keyboard::KEY_M		= false;

bool Keyboard::KEY_LCTRL	= false;
bool Keyboard::KEY_LSHIFT	= false;
bool Keyboard::KEY_SPACE	= false;
bool Keyboard::KEY_RCTRL	= false;
bool Keyboard::KEY_RSHIFT	= false;
	
bool Keyboard::KEY_UP		= false;
bool Keyboard::KEY_DOWN		= false;
bool Keyboard::KEY_LEFT		= false;
bool Keyboard::KEY_RIGHT	= false;
bool Keyboard::KEY_ESC		= false;

double Keyboard::MOUSEX		= 0;
double Keyboard::MOUSEY		= 0;

bool Keyboard::Keys[200];

Keyboard::Keyboard(){
	    
}

Keyboard::~Keyboard(){
    
}

bool Keyboard::get(std::string charcode){
	//converts and ascii key to raw Key
	std::transform(charcode.begin(), charcode.end(), charcode.begin(), ::tolower);
	if (charcode.length() == 1)
	{
		char c = *charcode.c_str();
		int code = c;
		return Keys[code];
	}
	else {
		if (charcode == "up") return Keys[196];
		if (charcode == "down") return Keys[197];
		if (charcode == "left") return Keys[198];
		if (charcode == "right") return Keys[199];
		if (charcode == "esc") return (bool)Key::KEY_ESC;
	}
	return 0;
}
Key Keyboard::ascii(std::string charcode){
	//converts and ascii key to raw Key
	std::transform(charcode.begin(), charcode.end(), charcode.begin(), ::tolower);
	if (charcode == "up") return Key::KEY_UP;
	if (charcode == "down") return Key::KEY_DOWN;
	if (charcode == "left") return Key::KEY_LEFT;
	if (charcode == "right") return Key::KEY_RIGHT;
	if (charcode == "esc") return Key::KEY_ESC;

	return Key::KEY_RCTRL;
}