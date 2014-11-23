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

Keyboard::Keyboard(){
	    
}

Keyboard::~Keyboard(){
    
}


Key Keyboard::ascii(std::string charcode){
	//converts and aascii key to Apex Key
	std::transform(charcode.begin(), charcode.end(), charcode.begin(), ::tolower);
	if (charcode == "f1") return Key::KEY_F1;
	if (charcode == "f2") return Key::KEY_F2;
	if (charcode == "f3") return Key::KEY_F3;
	if (charcode == "f4") return Key::KEY_F4;
	if (charcode == "f5") return Key::KEY_F5;
	if (charcode == "f6") return Key::KEY_F6;
	if (charcode == "f7") return Key::KEY_F7;
	if (charcode == "f8") return Key::KEY_F8;
	if (charcode == "f9") return Key::KEY_F9;
	if (charcode == "f10") return Key::KEY_F10;
	if (charcode == "f11") return Key::KEY_F11;
	if (charcode == "f12") return Key::KEY_F12;
	if (charcode == "1") return Key::KEY_1;
	if (charcode == "2") return Key::KEY_2;
	if (charcode == "3") return Key::KEY_3;
	if (charcode == "4") return Key::KEY_4;
	if (charcode == "5") return Key::KEY_5;
	if (charcode == "6") return Key::KEY_6;
	if (charcode == "7") return Key::KEY_7;
	if (charcode == "8") return Key::KEY_8;
	if (charcode == "9") return Key::KEY_9;
	if (charcode == "0") return Key::KEY_0;
	if (charcode == "q") return Key::KEY_Q;
	if (charcode == "w") return Key::KEY_W;
	if (charcode == "e") return Key::KEY_E;
	if (charcode == "r") return Key::KEY_R;
	if (charcode == "t") return Key::KEY_T;
	if (charcode == "y") return Key::KEY_Y;
	if (charcode == "u") return Key::KEY_U;
	if (charcode == "i") return Key::KEY_I;
	if (charcode == "o") return Key::KEY_O;
	if (charcode == "p") return Key::KEY_P;
	if (charcode == "a") return Key::KEY_A;
	if (charcode == "s") return Key::KEY_S;
	if (charcode == "d") return Key::KEY_D;
	if (charcode == "f") return Key::KEY_F;
	if (charcode == "g") return Key::KEY_G;
	if (charcode == "h") return Key::KEY_H;
	if (charcode == "j") return Key::KEY_J;
	if (charcode == "k") return Key::KEY_K;
	if (charcode == "l") return Key::KEY_L;
	if (charcode == "z") return Key::KEY_Z;
	if (charcode == "x") return Key::KEY_X;
	if (charcode == "c") return Key::KEY_C;
	if (charcode == "v") return Key::KEY_V;
	if (charcode == "b") return Key::KEY_B;
	if (charcode == "n") return Key::KEY_N;
	if (charcode == "m") return Key::KEY_M;
	if (charcode == "lctrl") return Key::KEY_LCTRL; 
	if (charcode == "lshift") return Key::KEY_LSHIFT;
	if (charcode == "space") return Key::KEY_SPACE;
	if (charcode == "rctrl") return Key::KEY_RCTRL;
	if (charcode == "rshift") return Key::KEY_RSHIFT;
	if (charcode == "up") return Key::KEY_UP;
	if (charcode == "down") return Key::KEY_DOWN;
	if (charcode == "left") return Key::KEY_LEFT;
	if (charcode == "right") return Key::KEY_RIGHT;
	if (charcode == "esc") return Key::KEY_ESC;

	return Key::KEY_F1;
}