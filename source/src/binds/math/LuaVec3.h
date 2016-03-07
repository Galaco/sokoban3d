#ifndef LUAVEC3_H
#define LUAVEC3_H

#include <math/Vec3.h>

#include <binds/LuaClass.h>

class LuaVec3 : public LuaClass{
public:
	LuaVec3();
	~LuaVec3();

	//luadata
	static const luaL_Reg luaBinds[];
	static int lua_Create(lua_State*);
	static int lua_X(lua_State*);
	static int lua_Y(lua_State*);
	static int lua_Z(lua_State*);
private:

};
#endif;