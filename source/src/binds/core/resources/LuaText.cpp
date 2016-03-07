#include "LuaText.h"

LuaText::LuaText()
{
}

LuaText::~LuaText()
{
}

const luaL_Reg LuaText::luaBinds[] = {
	{ "Create", lua_Create },
	{ NULL, NULL }
};

int LuaText::lua_Create(lua_State* L)
{
	LuaBinder binder(L);
	Text* text = new Text(binder.checkstring(1), binder.checknumber(2));

	binder.pushusertype(text, "Text");
	return 1;
}