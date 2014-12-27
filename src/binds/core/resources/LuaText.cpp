#include "LuaText.h"

LuaText::LuaText()
{
}

LuaText::~LuaText()
{
}

const luaL_Reg LuaText::luaBinds_f[] = {
	{ "new", lua_Create },
	{ NULL, NULL }
};

const luaL_Reg LuaText::luaBinds_m[] = {
	{ NULL, NULL }
};

int LuaText::lua_Create(lua_State* L)
{
	LuaBinder binder(L);
	Text* text = new Text(binder.checkstring(1), binder.checknumber(2));

	binder.pushusertype(text, "Text", sizeof(Text));
	return 1;
}