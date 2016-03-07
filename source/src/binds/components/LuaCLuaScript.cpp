#include "LuaCLuaScript.h"

LuaCLuaScript::LuaCLuaScript(){}
LuaCLuaScript::~LuaCLuaScript(){}

const luaL_Reg LuaCLuaScript::luaBinds[] = {
	{"Create", lua_Create},
	{"SetScript", lua_GetScript},
	{"GetScript", lua_SetScript},
	{"AddScript", lua_AddScript},
	{NULL, NULL}
};

int LuaCLuaScript::lua_Create(lua_State* L)
{
	LuaBinder binder(L);
	CLuaScript* v = new CLuaScript(L);
	binder.pushusertype(v, "CScript");
	return 1;
}

int LuaCLuaScript::lua_GetScript(lua_State* L)
{
	LuaBinder binder(L);
	CLuaScript* component = (CLuaScript*)binder.checkusertype(1, "CScript");
	LuaScript* v = component->getScript();
	binder.pushusertype(v, "Script");
	return 1;
}

int LuaCLuaScript::lua_SetScript(lua_State* L)
{
	LuaBinder binder(L);
	CLuaScript* component = (CLuaScript*)binder.checkusertype(1, "CScript");

	component->setScript((LuaScript*)binder.checkusertype(2, "Script") );
	return 0;
}

int LuaCLuaScript::lua_AddScript(lua_State* L)
{
	LuaBinder binder(L);
	CLuaScript* component = (CLuaScript*)binder.checkusertype(1, "CScript");

	component->addScript(binder.checkstring(2));
	return 0;
}