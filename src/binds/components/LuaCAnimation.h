#ifndef LUACANIMATION_H
#define LUACANIMATION_H

#include <binds/LuaClass.h>

#include <core/resources/Model.h>
#include <components/CAnimation.h>

class LuaCAnimation: public LuaClass{
public:
	LuaCAnimation();
	~LuaCAnimation();

	//luadata
	static const luaL_Reg luaBinds[];
	static int lua_Create(lua_State*);
	static int lua_SetAnimation(lua_State*);
	static int lua_GetAnimation(lua_State*);
	static int lua_AddAnimation(lua_State*);
};
#endif