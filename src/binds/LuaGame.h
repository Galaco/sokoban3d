/*********************************************************************
	Project: Dissertation
	Author: Josh Martin

	Name: Lua Game
	Description: Low level class all lua binding classes inherit from
*********************************************************************/
#ifndef LUAGAME_H
#define LUAGAME_H


#include <core/LuaBinder.h>

class LuaGame{
public:
	LuaGame();
	~LuaGame();

	static int lua_Shutdown(lua_State* L);

	static const luaL_Reg luaBinds_f[];
	static const luaL_Reg luaBinds_m[];

	
protected:

};
#endif