/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Lua Script
Description: Responsible for loading and running lua scripts. Is not 
			 automated. Must be called
*********************************************************************/
#ifndef LUASCRIPT_H
#define LUASCRIPT_H

#include <string>
#include <vector>
#include <assert.h>

//#include <Lua.hpp>
extern "C"{
	#include <lua.h>
	#include <lualib.h>
	#include <lauxlib.h>
	#include <luaconf.h>
}
#include <core/Logger.h>

typedef enum luaScriptStateTag
{
	LSS_WAITFRAME,
	LSS_WAITTIME,
	LSS_RUNNING,
	LSS_NOTLOADED,
	LSS_DONE
} LuaScriptState;

class LuaScript{
public:
	LuaScript();
	LuaScript(lua_State*);
	~LuaScript();

	void prepare(lua_State*);

	void runString(const char*);
	void runFile(std::string filename, std::string global = "");
	void callFunction(const char*);

	void update(float);

	LuaScriptState state;

private:
	void resumeScript(float);

	void handleError();
	void callFn( const char*, int);
	static lua_State* m_masterLuaState;
	lua_State* m_controlState;
	lua_State* threadState;
	int status;

	float time;
	float waitTimestamp;
	int waitFrame;

	std::string m_environmentId;
};
#endif