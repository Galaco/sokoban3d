#ifndef LUACSELECTABLE_H
#define LUACSELECTABLE_H

#include <binds/LuaClass.h>

#include <components/CSelectable.h>

class LuaCSelectable: public LuaClass{
public:
	LuaCSelectable();
	~LuaCSelectable();

	//luadata
	static const luaL_Reg luaBinds_f[];
	static const luaL_Reg luaBinds_m[];
	static int lua_Create(lua_State*);
	static int lua_GetHovered(lua_State*);
	static int lua_GetSelected(lua_State*);
};
#endif