#ifndef LUASCRIPT_H
#define LUASCRIPT_H

#include <string>
#include <vector>
#include <assert.h>

#include <Lua.hpp>

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
	LuaScript(lua_State*);
	~LuaScript();

	void runString(const char*);
	void runFile(std::string);
	void callFunction(const char*);

	void update(float);

	LuaScriptState state;

private:
	void resumeScript(float);

	void handleError();
	void callFn( const char*, int);
	lua_State* m_masterLuaState;
	lua_State* threadState;
	int status;

	Logger* m_Logger;
	float time;
	float waitTimestamp;
	int waitFrame;
};
#endif