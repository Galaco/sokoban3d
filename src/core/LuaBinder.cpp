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

void LuaBinder::initialize(const char* tname, const char* iname, const luaL_Reg* flist, const luaL_Reg* mlist){
	/*lua_rawgeti(L, LUA_REGISTRYINDEX, LUA_RIDX_GLOBALS);

	lua_newtable(L);
	luaL_setfuncs (L, flist, 0);
	lua_setglobal(L, tname);*/

	luaL_newmetatable(L, tname);
	lua_pushvalue(L, -1);
	lua_setfield(L, -2, "__index");
	luaL_setfuncs(L, mlist, 0);
	luaL_newlib(L, flist);
	/* lua_pushvalue(state, -1);*/
	lua_setglobal(L, tname);
	//lua_stack_dump(L);

	if (iname) {
		luaL_getmetatable(L, iname);
		lua_setfield(L, -2, "_base");  // mt._base = base mt
	}

	//lua_pop(L, 1);                    // pop metatable
	//if (iname) {
	//	luaL_getmetatable(L, iname);
	//	lua_setfield(L, -2, "__index"); // libtable.__index = base libtable
	//	lua_pushvalue(L, -1);          // duplicate libtable
	//	lua_setmetatable(L, -2);       // set itself as metatable
	//}
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
        
void LuaBinder::pushusertype( void* udata, const char* tname, int classSize){
	//lua_pushlightuserdata(L, udata);
	/*lua_pushvalue(L, -1);
	lua_pushstring(L, tname);
	lua_rawset(L, LUA_RIDX_GLOBALS);*/


	//luaL_setmetatable(L, tname);  //assign MyClass metatable


	void **data__ = (void **)lua_newuserdata(L, classSize);
	*data__ = udata;
	luaL_getmetatable(L, tname);
	lua_setmetatable(L, -2);
	//lua_stack_dump(L);
}

void* LuaBinder::checkusertype(int index, const char* tname){
	//void* udata = lua_touserdata(L, index);
	void* udata = (void**)luaL_checkudata(L, index, tname);
	if (udata == 0){// || checktype(udata, tname)) {
		//luaL_typeerror(L, index, tname);
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