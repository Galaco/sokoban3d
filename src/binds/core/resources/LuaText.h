#ifndef LUATEXT_H
#define LUATEXT_H

#include <core/resources/Text.h>

#include <binds/LuaClass.h>

class LuaText : public LuaClass{
public:
	LuaText();
	~LuaText();

	//luadata
	static int lua_Create(lua_State*);


	static const luaL_Reg luaBinds_f[];
	static const luaL_Reg luaBinds_m[];
};
#endif;