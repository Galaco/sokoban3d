#include "LuaLuaScript.h"

LuaLuaScript::LuaLuaScript()
{
}

LuaLuaScript::~LuaLuaScript()
{
}

const luaL_Reg LuaLuaScript::luaBinds[] = {
	{ "Create", lua_Create },
	{ "Load", lua_Load },
	{ NULL, NULL }
};

int LuaLuaScript::lua_Create(lua_State* L)
{
	LuaBinder binder(L);
	LuaScript* script = new LuaScript(L);

	binder.pushusertype(script, "LuaScript");
	return 1;
}
int LuaLuaScript::lua_Load(lua_State* L)
{
	LuaBinder binder(L);
	LuaScript* script = (LuaScript*)binder.checkusertype(1, "LuaScript");
	script->runFile(binder.checkstring(2));

	return 0;
}