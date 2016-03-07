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
        
	void initialize(const char*, const luaL_Reg*);
        
	void pushnumber(double);	//Push a number to Lua
	double checknumber(int);	//Pull a number from Lua
        
	void pushstring(const char*);	//Push a string to Lua	
	const char* checkstring(int);	//Pull a string from Lua
        
	void pushusertype(void*, const char*);	//Push any class type to Lua
	void* checkusertype(int, const char*);	//Pull any class type from Lua
private:
	int checktype(void*, const char*);
	void releaseusertype(void*);
    
    
	lua_State* L;
};
#endif
