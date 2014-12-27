/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Lua Binder
Description: Responsible for Lua Stack handling. Mainly pushes and 
			 pulls data on the the Lua stack.
*********************************************************************/
#ifndef LUABINDER_H
#define LUABINDER_H

#include <string>

#include <lua.hpp>

class LuaBinder {
public:
	LuaBinder();
	LuaBinder(lua_State*);
	~LuaBinder();

	void setLuaState(lua_State*);
        
	void initialize(const char* tname, const char* iname, const luaL_Reg* functionList, const luaL_Reg* memberList);
        
	void pushnumber(double);
	double checknumber(int);
        
	void pushstring(const char*);
	const char* checkstring(int);
        
	void pushusertype(void*, const char*, int classSize);
	void* checkusertype(int, const char*);
private:
	int checktype(void*, const char*);
	void releaseusertype(void*);
    
    
	lua_State* L;
};
#endif
