/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Component LuaScript
Description: Store a luascript(s) for usage with script system
*********************************************************************/
#ifndef CLUASCRIPT_H
#define CLUASCRIPT_H

#include <string>
#include <Lua.hpp>

#include <core/Component.h>
#include <core/resources/LuaScript.h>

class CLuaScript: public Component {
public:
	CLuaScript();
	CLuaScript(lua_State*);
	~CLuaScript();

	void setLuaState(lua_State*);

	void setScript(LuaScript*);
	LuaScript* getScript();
	void addScript(const char* file);
	
private:
	static lua_State* m_masterLuaState;
	LuaScript m_script;

};
#endif