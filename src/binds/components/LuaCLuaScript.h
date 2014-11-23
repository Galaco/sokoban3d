#ifndef LUACLUASCRIPT_H
#define LUACLUASCRIPT_H

#include <binds/LuaClass.h>

#include <components/CLuaScript.h>

class LuaCLuaScript: public LuaClass{
public:
	LuaCLuaScript();
	~LuaCLuaScript();

	//luadata
	static const luaL_Reg luaBinds[];
	static int lua_Create(lua_State*);
	static int lua_GetScript(lua_State*);
	static int lua_SetScript(lua_State*);
	static int lua_AddScript(lua_State*);
};
#endif