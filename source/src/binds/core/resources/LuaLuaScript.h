#ifndef LUALUASCRIPT_H
#define LUALUASCRIPT_H

#include <core/resources/LuaScript.h>

#include <binds/LuaClass.h>

class LuaLuaScript : public LuaClass{
public:
	LuaLuaScript();
	~LuaLuaScript();

	//luadata
	static int lua_Create(lua_State*);
	static int lua_Load(lua_State*);





	static const luaL_Reg luaBinds[];
};
#endif;