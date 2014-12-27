#ifndef LUAKEYBOARD_H
#define LUAKEYBOARD_H

#include <binds/LuaClass.h>

#include <core/helpers/Keyboard.h>

class LuaKeyboard: public LuaClass{
public:
	LuaKeyboard();
	~LuaKeyboard();


	//luadata
	static const luaL_Reg luaBinds_f[];
	static const luaL_Reg luaBinds_m[];
	static int lua_KeyDown(lua_State*);
};
#endif