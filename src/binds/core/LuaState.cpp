#include "LuaState.h"

LuaState::LuaState(){
}

LuaState::~LuaState(){
}

const luaL_Reg LuaState::luaBinds[] = {
	{ "Create", lua_Create },
	{ "CreateSokoban", lua_CreateSokoban },
	{"Destroy", lua_Destroy},
	{"AddEntity", lua_AddEntity},
	{"AddCamera", lua_AddCamera },
	{"GetDirectionalLight", lua_GetDirectionalLight },
	{"GetState", lua_GetState},
	{ "RequestPriority", lua_RequestPriority },
	{ "AddPointLight", lua_AddPointLight },
	{ "Deprioritise", lua_Deprioritise },
	{NULL, NULL}
};

int LuaState::lua_Create(lua_State* L)
{
	LuaBinder binder(L);	

	State& s = StateManager::addState(binder.checkstring(1));
	s.load(binder.checkstring(2));
	binder.pushusertype(&s, "State");
	return 1;
}

int LuaState::lua_CreateSokoban(lua_State* L)
{
	LuaBinder binder(L);
	State& s = StateManager::addState(binder.checkstring(1));
	binder.pushusertype(&s, "State");

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
	State& state = StateManager::getState(binder.checkstring(2));
	state.addEntity(*entity);

	return 0;
}

int LuaState::lua_AddCamera(lua_State* L)
{
	LuaBinder binder(L);
	Camera cam = *static_cast<Camera*>(binder.checkusertype(1, "Camera"));
	State& state = StateManager::getState(binder.checkstring(2));

	state.addCamera(*static_cast<Camera*>(binder.checkusertype(1, "Camera")));

	return 0;
}

int LuaState::lua_GetDirectionalLight(lua_State* L)
{
	LuaBinder binder(L);
	State& state = StateManager::getState(binder.checkstring(1));
	binder.pushusertype(&state.getDirectionalLight(), "DirectionalLight");

	return 1;
}


int LuaState::lua_GetState(lua_State* L)
{
	LuaBinder binder(L);

	State& state = StateManager::getState(binder.checkstring(1));
	binder.pushusertype(&state, "State");

	return 1;
}

int LuaState::lua_RequestPriority(lua_State* L)
{
	LuaBinder binder(L);
	State& s = StateManager::getState(binder.checkstring(1));
	s.wantsPriority() = true;
	s.priority = StateManager::getActiveState()->priority + 1;

	return 0;
}

int LuaState::lua_AddPointLight(lua_State* L){
	LuaBinder binder(L);
	PointLight* light = static_cast<PointLight*>(binder.checkusertype(1, "PointLight"));
	State& state = StateManager::getState(binder.checkstring(2));

	state.addPointLight(*light);

	return 0;
}

int LuaState::lua_Deprioritise(lua_State* L)
{
	LuaBinder binder(L);
	State& s = StateManager::getState(binder.checkstring(1));

	s.canDeprioritise() = true;

	return 0;
}