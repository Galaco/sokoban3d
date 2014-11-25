#ifndef LUACGRAPHICS_H
#define LUACGRAPHICS_H

#include <binds/LuaClass.h>

#include <components/CGraphics.h>

class LuaCGraphics: public LuaClass{
public:
	LuaCGraphics();
	~LuaCGraphics();

	//luadata
	static const luaL_Reg luaBinds[];
	static int lua_Create(lua_State*);
	static int lua_GetModel(lua_State*);
	static int lua_SetModel(lua_State*);
	static int lua_AddModel(lua_State*);
	static int lua_AddTexture(lua_State*);
	static int lua_SetRenderMode(lua_State*);
};
#endif