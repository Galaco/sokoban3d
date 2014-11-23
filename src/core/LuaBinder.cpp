#include "LuaBinder.h"

LuaBinder::LuaBinder(){}

LuaBinder::LuaBinder(lua_State* L){
	this->L = L;
}

LuaBinder::~LuaBinder(){
	L = nullptr;
}


void LuaBinder::setLuaState(lua_State* state){
	L = state;
}

void LuaBinder::initialize(const char* tname, const luaL_Reg* flist){
	//-- get global environment table from registry
	lua_rawgeti(L, LUA_REGISTRYINDEX, LUA_RIDX_GLOBALS);

	lua_newtable(L);
	luaL_setfuncs (L, flist, 0);
	lua_setglobal(L, tname);
}
        
void LuaBinder::pushnumber(double v){
	lua_pushnumber(L, v);
}

double LuaBinder::checknumber(int index){
	return luaL_checknumber(L, index);
}
        
void LuaBinder::pushstring(const char* s){
	lua_pushstring(L, s);
}

const char* LuaBinder::checkstring(int index){
	return luaL_checkstring(L, index);
}
        
void LuaBinder::pushusertype( void* udata, const char* tname){
	lua_pushlightuserdata(L, udata);
	/*lua_pushvalue(L, -1);
	lua_pushstring(L, tname);
	lua_rawset(L, LUA_RIDX_GLOBALS);*/
}

void* LuaBinder::checkusertype(int index, const char* tname){
	void* udata = lua_touserdata(L, index);
	if (udata == 0 ){//|| checktype(udata, tname)) {
		//luaL_typerror(L, index, tname);
	}
	return udata;
}


int LuaBinder::checktype(void* udata, const char* tname){
	lua_pushlightuserdata(L, udata);
	lua_rawget(L, LUA_RIDX_GLOBALS);
	const char* stored_tname = lua_tostring(L, -1);
	int result = stored_tname && strcmp(stored_tname, tname)==0;
	lua_pop(L,1);
	return result;
}

void LuaBinder::releaseusertype(void* udata){
	lua_pushlightuserdata(L, udata);
	lua_pushnil(L);
	lua_settable(L, LUA_RIDX_GLOBALS);
}