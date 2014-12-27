#ifndef LUACAMERA_H
#define LUACAMERA_H

#include <core/StateManager.h>
#include <core/Camera.h>
#include <core/resources/Skybox.h>

#include <binds/LuaClass.h>

class LuaCamera : public LuaClass{
public:
	LuaCamera();
	~LuaCamera();

	//luadata
	//Lua binds
	static int lua_Create(lua_State*);
	static int lua_Destroy(lua_State*);
	static int lua_SetParent(lua_State*);
	static int lua_AddSkybox(lua_State*);
	static int lua_ActiveCamera(lua_State*);
	static int lua_GoForward(lua_State*);
	static int lua_GoBackward(lua_State*);
	static int lua_GoLeft(lua_State*);
	static int lua_GoRight(lua_State*);
	static int lua_GoUp(lua_State*);
	static int lua_GoDown(lua_State*);
	static int lua_GetTransform(lua_State*);
	static int lua_SetTransform(lua_State*);
	static int lua_ToggleMouse(lua_State*);
	static int lua_Find(lua_State*);
	static int lua_SetActive(lua_State*);

	static const luaL_Reg luaBinds_f[];
	static const luaL_Reg luaBinds_m[];
};
#endif;