/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Keyboard
Description: Stores state of keyboard keys. Is not in any way 
			 optimised
*********************************************************************/
#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <string>
#include <algorithm>

#include <core/Logger.h>

enum Key{
	KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12, 
	KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0, 
	KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P, KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K, KEY_L, 
	KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_M, 
	KEY_LCTRL, KEY_LSHIFT, KEY_SPACE, KEY_RCTRL, KEY_RSHIFT, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT, KEY_ESC, MOUSEX, MOUSEY
};

class Keyboard {
public:
	Keyboard();
	~Keyboard();

	static Key ascii(std::string);

	static bool get(std::string);
	static bool KEY_F1, KEY_F2, KEY_F3, KEY_F4, KEY_F5, KEY_F6, KEY_F7, KEY_F8, KEY_F9, KEY_F10, KEY_F11, KEY_F12;

	static bool KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9, KEY_0;

	static bool KEY_Q, KEY_W, KEY_E, KEY_R, KEY_T, KEY_Y, KEY_U, KEY_I, KEY_O, KEY_P;
	static bool KEY_A, KEY_S, KEY_D, KEY_F, KEY_G, KEY_H, KEY_J, KEY_K, KEY_L;
	static bool KEY_Z, KEY_X, KEY_C, KEY_V, KEY_B, KEY_N, KEY_M;
	
	static bool KEY_LCTRL, KEY_LSHIFT, KEY_SPACE, KEY_RCTRL, KEY_RSHIFT, KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT;

	static bool KEY_ESC;
	
	static double MOUSEX, MOUSEY;

	static bool Keys[200];

};
#endif
