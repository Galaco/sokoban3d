#include "LuaKeyboard.h"

LuaKeyboard::LuaKeyboard()
{
}

LuaKeyboard::~LuaKeyboard()
{
}

const luaL_Reg LuaKeyboard::luaBinds[] = {
	{"KeyDown", lua_KeyDown},
	{NULL, NULL}
};

int LuaKeyboard::lua_KeyDown(lua_State* L)
{
	LuaBinder binder(L);
	switch(Keyboard::ascii(binder.checkstring(1)))
	{
		case Key::KEY_1:
			return Keyboard::KEY_1;
			break;
		case Key::KEY_2:
			return Keyboard::KEY_2;
			break;
		case Key::KEY_3:
			return Keyboard::KEY_3;
			break;
		case Key::KEY_4:
			return Keyboard::KEY_4;
			break;
		case Key::KEY_5:
			return Keyboard::KEY_5;
			break;
		case Key::KEY_6:
			return Keyboard::KEY_6;
			break;
		case Key::KEY_7:
			return Keyboard::KEY_7;
			break;
		case Key::KEY_8:
			return Keyboard::KEY_8;
			break;
		case Key::KEY_9:
			return Keyboard::KEY_9;
			break;
		case Key::KEY_0:
			return Keyboard::KEY_0;
			break;
		case Key::KEY_Q:
			return Keyboard::KEY_Q;
			break;
		case Key::KEY_W:
			return Keyboard::KEY_W;
			break;
		case Key::KEY_E:
			return Keyboard::KEY_E;
			break;
		case Key::KEY_R:
			return Keyboard::KEY_R;
			break;
		case Key::KEY_T:
			return Keyboard::KEY_T;
			break;
		case Key::KEY_Y:
			return Keyboard::KEY_Y;
			break;
		case Key::KEY_U:
			return Keyboard::KEY_U;
			break;
		case Key::KEY_I:
			return Keyboard::KEY_I;
			break;
		case Key::KEY_O:
			return Keyboard::KEY_O;
			break;
		case Key::KEY_P:
			return Keyboard::KEY_P;
			break;
		case Key::KEY_A:
			return Keyboard::KEY_A;
			break;
		case Key::KEY_S:
			return Keyboard::KEY_S;
			break;
		case Key::KEY_D:
			return Keyboard::KEY_D;
			break;
		case Key::KEY_F:
			return Keyboard::KEY_F;
			break;
		case Key::KEY_G:
			return Keyboard::KEY_G;
			break;
		case Key::KEY_H:
			return Keyboard::KEY_H;
			break;
		case Key::KEY_J:
			return Keyboard::KEY_J;
			break;
		case Key::KEY_K:
			return Keyboard::KEY_K;
			break;
		case Key::KEY_L:
			return Keyboard::KEY_L;
			break;
		case Key::KEY_Z:
			return Keyboard::KEY_Z;
			break;
		case Key::KEY_X:
			return Keyboard::KEY_X;
			break;
		case Key::KEY_C:
			return Keyboard::KEY_C;
			break;
		case Key::KEY_V:
			return Keyboard::KEY_V;
			break;
		case Key::KEY_B:
			return Keyboard::KEY_B;
			break;
		case Key::KEY_N:
			return Keyboard::KEY_N;
			break;
		case Key::KEY_M:
			return Keyboard::KEY_M;
			break;
		case Key::KEY_ESC:
			return Keyboard::KEY_ESC;
			break;
		default:
			return 0;
	}
	
	return 1;
}