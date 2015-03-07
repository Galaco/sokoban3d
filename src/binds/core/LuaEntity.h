#ifndef LUAENTITY_H
#define LUAENTITY_H

#include <core/Entity.h>
#include <core/StateManager.h>

#include <binds/LuaClass.h>
#include <components/CGraphics.h>

class LuaEntity : public LuaClass{
public:
	LuaEntity();
	~LuaEntity();

	//luadata
	//Lua binds
	static int lua_Create(lua_State*);
	static int lua_Destroy(lua_State*);
	static int lua_AddComponent(lua_State*);
	static int lua_GetTransform(lua_State*);
	static int lua_SetTransform(lua_State*);
	static int lua_GetComponent(lua_State* L);

	static int lua_Find(lua_State*);

	static const luaL_Reg luaBinds[];
};
#endif;