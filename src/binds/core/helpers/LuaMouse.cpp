#include "LuaMouse.h"

LuaMouse::LuaMouse()
{
}

LuaMouse::~LuaMouse()
{
}

const luaL_Reg LuaMouse::luaBinds_f[] = {
	{ NULL, NULL }
};

const luaL_Reg LuaMouse::luaBinds_m[] = {
	{ "Show", lua_Show },
	{ "Hide", lua_Hide },
	{ "Get", lua_Get },
	{ "Lock", lua_Lock },
	{ "Unlock", lua_Unlock },
	{ "Pressed", lua_Pressed },
	{ NULL, NULL }
};


int LuaMouse::lua_Show(lua_State* L)
{
	LuaBinder binder(L);

	Mouse::show();

	return 0;
}
int LuaMouse::lua_Hide(lua_State* L)
{
	LuaBinder binder(L);

	Mouse::hide();

	return 0;
}
int LuaMouse::lua_Get(lua_State* L)
{
	LuaBinder binder(L);
	std::string axis = binder.checkstring(1);
	if (axis == "x")
	{
		binder.pushnumber(Mouse::_X);
		return 1;
	}
	if (axis == "y")
	{
		binder.pushnumber(Mouse::_Y);
		return 1;
	}

	return 0;
}
int LuaMouse::lua_Lock(lua_State* L)
{
	LuaBinder binder(L);

	Mouse::lock();

	return 0;
}
int LuaMouse::lua_Unlock(lua_State* L)
{
	LuaBinder binder(L);

	Mouse::unlock();

	return 0;
}
int LuaMouse::lua_Pressed(lua_State* L)
{
	LuaBinder binder(L);

	std::string button = binder.checkstring(1);

	if (button == "left")
	{
		return Mouse::_LEFT;
	}
	if (button == "right")
	{
		return Mouse::_RIGHT;
	}

	return 0;
}

