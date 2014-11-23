#ifndef LUAPOINTLIGHT_H
#define LUAPOINTLIGHT_H

#include <core/resources/PointLight.h>

#include <binds/LuaClass.h>

class LuaPointLight : public LuaClass{
public:
	LuaPointLight();
	~LuaPointLight();

	//luadata
	//State requests
	static int lua_Create(lua_State*);
	static int lua_Destroy(lua_State*);
	static int lua_SetColor(lua_State*);
	static int lua_GetColor(lua_State*);
	static int lua_SetAmbience(lua_State*);
	static int lua_GetAmbience(lua_State*);
	static int lua_SetDiffuse(lua_State*);
	static int lua_GetDiffuse(lua_State*);



	//StateManager requests
	static int lua_GetState(lua_State*);
	static int lua_RequestPriority(lua_State*);

	static const luaL_Reg luaBinds[];
};
#endif;