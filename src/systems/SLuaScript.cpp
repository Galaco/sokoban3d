#include "SLuaScript.h"

std::vector<CLuaScript*> SLuaScript::CLuaScriptCache;

SLuaScript::SLuaScript(){
	m_masterLuaState = nullptr;
}

SLuaScript::~SLuaScript(){
}

void SLuaScript::initialize(){
	m_masterLuaState = luaL_newstate();	//Initialize Lua
	luaL_openlibs( m_masterLuaState );
	m_luaBinds.setLuaState(m_masterLuaState);
	m_luaBinds.bindObjects();	//Bind objects to lua
}

lua_State* SLuaScript::getMasterState(){
	return m_masterLuaState;
}

LuaScript* SLuaScript::createScript(){
	LuaScript* l = new LuaScript(m_masterLuaState);
	m_globalScripts.push_back(l);
	return l;
}

void SLuaScript::update(float dt){
	if ((m_CurrentState != m_PreviousState) || Scene::ForceRecache)
	{
		rebuildCache();
	}

	auto it = CLuaScriptCache.begin();		//Update entity scripts
	while (it != CLuaScriptCache.end())
	{
		(*it)->getScript()->update(dt);	
		++it;
	}
	
	auto itRaw = m_globalScripts.begin();	//Update script with no attachment
	while(itRaw != m_globalScripts.end()) {
		(*itRaw)->update(dt);
		++itRaw;
	}
}


void SLuaScript::deleteScript(LuaScript* scriptptr)
{
	for( unsigned int i=0; i < m_globalScripts.size(); ++i)
	{
		if (m_globalScripts[i] == scriptptr)
		{
			delete m_globalScripts[i];
			m_globalScripts.erase(m_globalScripts.begin()+i);
			return;
		}
	}
}

void SLuaScript::rebuildCache()
{
	CLuaScriptCache.clear();	//Empty cache
	std::map<std::string, Entity*> entityList = m_CurrentState->getEntities();
	auto it = entityList.begin();
	while (it != entityList.end())
	{
		std::vector<Component*> cList = (*it).second->getComponentsByType("LuaScript");
		auto CIterator = cList.begin();
		while (CIterator != cList.end())
		{
			CLuaScriptCache.push_back(static_cast<CLuaScript*>(*CIterator));	//Insert object into cache
			++CIterator;
		}
		++it;
	}

	std::vector<Camera*> camList = m_CurrentState->getCameras();
	auto it2 = camList.begin();
	while (it2 != camList.end())
	{
		std::vector<Component*> cList = (*it2)->getComponentsByType("LuaScript");
		auto CIterator = cList.begin();
		while (CIterator != cList.end())
		{
			CLuaScriptCache.push_back(static_cast<CLuaScript*>(*CIterator));	//Insert camera into cache
			++CIterator;
		}
		++it2;
	}
}