#include "LuaState.h"

LuaState::LuaState(){
}

LuaState::~LuaState(){
}

const luaL_Reg LuaState::luaBinds[] = {
	{"Create", lua_Create},
	{"Destroy", lua_Destroy},
	{"AddEntity", lua_AddEntity},
	{"AddCamera", lua_AddCamera },
	{"GetDirectionalLight", lua_GetDirectionalLight },
	{"GetState", lua_GetState},
	{ "RequestPriority", lua_RequestPriority },
	{ "AddPointLight", lua_AddPointLight },
	{ "AddScript", lua_AddScript },
	{NULL, NULL}
};

int LuaState::lua_Create(lua_State* L)
{
	LuaBinder binder(L);	
	State* state = StateManager::getState(binder.checkstring(1));
	if (state == nullptr)
	{
		State* s = new State;
		StateManager::addState(s, binder.checkstring(1));
		binder.pushusertype(s, "State");
	} 
	else {
		binder.pushusertype(state, "State");
	}
	return 1;
}

int LuaState::lua_Destroy(lua_State* L)
{
	LuaBinder binder(L);
	State* state = (State*)binder.checkusertype(1, "State");
	delete state;
	return 0;
}

int LuaState::lua_AddEntity(lua_State* L)
{
	LuaBinder binder(L);
	Entity* entity = static_cast<Entity*>(binder.checkusertype(1, "Entity"));
	State* state = StateManager::getState(binder.checkstring(2));
	if (state != nullptr)
	{
		state->addEntity(entity);
	}

	return 0;
}

int LuaState::lua_AddCamera(lua_State* L)
{
	LuaBinder binder(L);
	Camera* cam = static_cast<Camera*>(binder.checkusertype(1, "Camera"));
	State* state = StateManager::getState(binder.checkstring(2));
	if (state != nullptr)
	{
		state->addCamera(cam);
	}

	return 0;
}

int LuaState::lua_GetDirectionalLight(lua_State* L)
{
	LuaBinder binder(L);
	State* state = StateManager::getState(binder.checkstring(1));
	if (state == nullptr) 
	{
		return 0;
	}
	DirectionalLight* light = state->getDirectionalLight();
	binder.pushusertype(light, "DirectionalLight");

	return 1;
}


int LuaState::lua_GetState(lua_State* L)
{
	LuaBinder binder(L);

	State* state = StateManager::getState(binder.checkstring(1));
	if (state == nullptr)
	{
		return 0;
	}
	binder.pushusertype(state, "State");

	return 1;
}

int LuaState::lua_RequestPriority(lua_State* L)
{
	LuaBinder binder(L);
	State* s = StateManager::getState(binder.checkstring(1));
	if (s != nullptr)
	{
		s->wantsPriority() = true;
		s->priority = StateManager::getActiveState()->priority + 1;
	}

	return 0;
}

int LuaState::lua_AddPointLight(lua_State* L){
	LuaBinder binder(L);
	PointLight* light = static_cast<PointLight*>(binder.checkusertype(1, "PointLight"));
	State* state = StateManager::getState(binder.checkstring(2));
	if (state != nullptr)
	{
		state->addPointLight(light);
	}

	return 0;
}

int LuaState::lua_AddScript(lua_State* L){
	LuaBinder binder(L);
	LuaScript* script = static_cast<LuaScript*>(binder.checkusertype(1, "LuaScript"));
	State* state = StateManager::getState(binder.checkstring(2));
	if (state != nullptr)
	{
		state->addScript(script);
	}

	return 0;
}