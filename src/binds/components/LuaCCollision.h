#ifndef LUACCOLLISION_H
#define LUACCOLLISION_H

#include <binds/LuaClass.h>

#include <components/CGraphics.h>
#include <components/CCollision.h>

class LuaCCollision: public LuaClass{
public:
	LuaCCollision();
	~LuaCCollision();

	//luadata
	static const luaL_Reg luaBinds_f[];
	static const luaL_Reg luaBinds_m[];
	static int lua_Create(lua_State*);
	static int lua_CreateCollisionModel(lua_State*);
};
#endif