#include "LuaVec3.h"

LuaVec3::LuaVec3(){
}

LuaVec3::~LuaVec3(){

}

const luaL_Reg LuaVec3::luaBinds_f[] = {
	{ "new", lua_Create },
	{ NULL, NULL }
};

const luaL_Reg LuaVec3::luaBinds_m[] = {
	{ "x", lua_X },
	{ "y", lua_Y },
	{ "z", lua_Z },
	{NULL, NULL}
};

int LuaVec3::lua_Create(lua_State* L){
	LuaBinder binder(L);
	Vec3* v = new Vec3((float)binder.checknumber(1), (float)binder.checknumber(2), (float)binder.checknumber(3));

	binder.pushusertype(v, "Vec3", sizeof(Vec3));
	return 1;
}


int LuaVec3::lua_X(lua_State* L){
	LuaBinder binder(L);

    Vec3* entity = (Vec3*)binder.checkusertype(1, "Vec3");
	binder.pushnumber(entity->x);

	return 1;
}

int LuaVec3::lua_Y(lua_State* L){
	LuaBinder binder(L);

	Vec3* entity = (Vec3*)binder.checkusertype(1, "Vec3");
	binder.pushnumber(entity->y);

	return 1;

}

int LuaVec3::lua_Z(lua_State* L){
	LuaBinder binder(L);

	Vec3* entity = (Vec3*)binder.checkusertype(1, "Vec3");
	binder.pushnumber(entity->z);

	return 1;

}