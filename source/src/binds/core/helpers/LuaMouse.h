/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: LuaMouse
Description: Stores mouse information
*********************************************************************/
#ifndef LUAMOUSE_H
#define LUAMOUSE_H

#include <binds/LuaClass.h>
#include <core/helpers/Mouse.h>

class LuaMouse {
public:
	LuaMouse();
	~LuaMouse();

	static const luaL_Reg luaBinds[];
	static int lua_Show(lua_State*);
	static int lua_Hide(lua_State*);
	static int lua_Get(lua_State*);
	static int lua_Lock(lua_State*);
	static int lua_Unlock(lua_State*);

	static int lua_Pressed(lua_State*);

};
#endif
