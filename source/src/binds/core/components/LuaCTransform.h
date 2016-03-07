#ifndef LUACTRANSFORM_H
#define LUACTRANSFORM_H

#include <binds/LuaClass.h>

#include <core/components/CTransform.h>
#include <math/Vec3.h>

class LuaCTransform: public LuaClass{
public:
	LuaCTransform();
	~LuaCTransform();

	//luadata
	static const luaL_Reg luaBinds[];
	static int lua_Create(lua_State*);
	static int lua_GetPosition(lua_State*);
	static int lua_SetPosition(lua_State*);
	static int lua_GetOrientation(lua_State*);
	static int lua_SetOrientation(lua_State*);
	static int lua_GetScale(lua_State*);
	static int lua_SetScale(lua_State*);
};
#endif