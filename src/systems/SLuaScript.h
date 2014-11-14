#ifndef SLUASYSTEM_H
#define SLUASYSTEM_H

#include <map>
#include <vector>
#include <Lua.hpp>

#include <core/Logger.h>
#include <core/System.h>
#include <core/resources/LuaScript.h>

#include "lua/LuaObjectBinds.h"
#include "../components/CLuaScript.h"

class SLuaScript: public System {
public:
	SLuaScript();
	~SLuaScript();

	void initialize();
        
	lua_State* getMasterState();

	LuaScript* createScript();

	void deleteScript(LuaScript* scriptptr);

	void update(float);

private:
	lua_State* m_masterLuaState;
	LuaObjectBinds* m_luaBinds;

	std::vector<LuaScript*> m_globalScripts;
};
#endif
