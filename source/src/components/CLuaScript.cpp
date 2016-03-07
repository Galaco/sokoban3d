#include "CLuaScript.h"
#include <core/Entity.h>

lua_State* CLuaScript::m_masterLuaState;

CLuaScript::CLuaScript(){
	m_type="LuaScript";
}

CLuaScript::CLuaScript(lua_State* s){
	if (!m_masterLuaState){
		m_masterLuaState = s;
	}
}

CLuaScript::~CLuaScript(){
	m_masterLuaState = nullptr;
}

void CLuaScript::setLuaState(lua_State* s){
	m_masterLuaState = s;
}


void CLuaScript::setScript(LuaScript* script){
	m_script = *script;
}

LuaScript* CLuaScript::getScript(){
	return &m_script;
}

void CLuaScript::addScript(const char* file){
	m_script.prepare(m_masterLuaState);
	std::string envName = "";
	if (m_entity)
	{
		envName = m_entity->getId();
	}
	m_script.runFile(file, envName);
}