#include "LuaKeyboard.h"

LuaKeyboard::LuaKeyboard()
{
}

LuaKeyboard::~LuaKeyboard()
{
}

const luaL_Reg LuaKeyboard::luaBinds_f[] = {
	{ NULL, NULL }
};


const luaL_Reg LuaKeyboard::luaBinds_m[] = {
	{"KeyDown", lua_KeyDown},
	{NULL, NULL}
};

int LuaKeyboard::lua_KeyDown(lua_State* L)
{
	LuaBinder binder(L);
	return Keyboard::get(binder.checkstring(1));
}