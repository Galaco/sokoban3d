/*********************************************************************
	Project: Dissertation
	Author: Josh Martin

	Name: Lua Class
	Description: Low level class all lua binding classes inherit from
*********************************************************************/
#ifndef LUAEXCEPTION_H
#define LUAEXCEPTION_H

#include <iostream>

//#include <Lua.hpp>
extern "C"{
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
	#include <luaconf.h>
}

class lua_exception : public std::exception{
private:
	bool committed;	// == luaD_rawrunprotected has handled the exception
	struct lua_longjmp *const errorJmp;



public:
	struct lua_State* const L;

	lua_exception(struct lua_State *L, struct lua_longjmp *errorJmp);
	~lua_exception();


	/*override*/ const char *what() const;

	void commit() { committed = true; }
};
#endif