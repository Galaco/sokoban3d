#include "LuaGame.h"

#include <Game.h>

LuaGame::LuaGame(){

}

LuaGame::~LuaGame() {

}
const luaL_Reg LuaGame::luaBinds[] = {
	{ "Close", lua_Shutdown },
	{ NULL, NULL }
};



int LuaGame::lua_Shutdown(lua_State* L)
{
	Game::close();

	return 0;
}