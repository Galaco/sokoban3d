#ifndef LUASOKOBAN_H
#define LUASOKOBAN_H

#include "../../GAME/Sokoban.h"
#include <core/SceneManager.h>

#include <binds/LuaClass.h>

class LuaSokoban : public LuaClass{
public:
	LuaSokoban();
	~LuaSokoban();

	//luadata
	static int lua_CanPlayerMove(lua_State* L);
	static int lua_CanBlockMove(lua_State* L);
	static int lua_PlayerMove(lua_State* L);
	static int lua_BlockMove(lua_State* L);

	static int lua_GetCurrentFace(lua_State* L);

	static const luaL_Reg luaBinds[];
};
#endif;