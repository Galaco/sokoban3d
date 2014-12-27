#ifndef LUADIRECTIONALLIGHT_H
#define LUADIRECTIONALLIGHT_H

#include <core/resources/DirectionalLight.h>
#include <math/Vec3.h>

#include <binds/LuaClass.h>

class LuaDirectionalLight : public LuaClass{
public:
	LuaDirectionalLight();
	~LuaDirectionalLight();

	//luadata
	static int lua_Create(lua_State*);
	static int lua_Destroy(lua_State*);

	static int lua_SetColor(lua_State*);
	static int lua_GetColor(lua_State*);
	static int lua_SetAmbience(lua_State*);
	static int lua_GetAmbience(lua_State*);
	static int lua_SetDiffuse(lua_State*);
	static int lua_GetDiffuse(lua_State*);
	static int lua_SetDirection(lua_State*);
	static int lua_GetDirection(lua_State*);


	static const luaL_Reg luaBinds_f[];
	static const luaL_Reg luaBinds_m[];
};
#endif;