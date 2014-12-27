#include "LuaEntity.h"

LuaEntity::LuaEntity()
{
}

LuaEntity::~LuaEntity()
{
}

const luaL_Reg LuaEntity::luaBinds_f[] = {
	{ "new", lua_Create },
	{ "__gc", lua_Destroy },
	{ NULL, NULL }
};

const luaL_Reg LuaEntity::luaBinds_m[] = {
	{"Create", lua_Create},
	{"Destroy", lua_Destroy},
	{"AddComponent", lua_AddComponent},
	{"GetTransform", lua_GetTransform},
	{"SetTransform", lua_SetTransform},
	{"Find", lua_Find },
	{NULL, NULL}
};

int LuaEntity::lua_Create(lua_State* L)
{
	LuaBinder binder(L);
	if (binder.checkstring(1))
	{
		/*Entity** c = (Entity**)lua_newuserdata(L, sizeof(Entity*));
		*c = new Entity();
		binder.pushusertype(c, "Entity");*/

		Entity* entity = new Entity(binder.checkstring(1));
		binder.pushusertype(entity, "Entity", sizeof(Entity));

		return 1;
	}

	return 0;
}

int LuaEntity::lua_Destroy(lua_State* L)
{
	LuaBinder binder(L);
	Entity* entity = (Entity*)binder.checkusertype(1, "Entity");
	delete entity;
	return 0;
}

int LuaEntity::lua_AddComponent(lua_State* L)
{
	LuaBinder binder(L);

	Entity* entity =* (Entity**)binder.checkusertype(1, "Entity");
	Component* component =* (Component**)binder.checkusertype(2, "Component");
	const char * c = binder.checkstring(3);
	entity->addComponent(component, c);

	return 0;
}

int LuaEntity::lua_GetTransform(lua_State* L)
{
	LuaBinder binder(L);

	Entity* entity = (Entity*)binder.checkusertype(1, "Camera");
	binder.pushusertype(entity->GetTransform(), "Transform", sizeof(CTransform));

	return 1;
}

int LuaEntity::lua_SetTransform(lua_State* L)
{
	LuaBinder binder(L);

	Entity* entity = (Entity*)binder.checkusertype(1, "Entity");
	CTransform* component = (CTransform*)binder.checkusertype(2, "Component");

	entity->SetTransform(component);
	return 0;
}

int LuaEntity::lua_Find(lua_State* L)
{
	LuaBinder binder(L);

	State* state = StateManager::getActiveState();
	Entity* e = state->getEntity(binder.checkstring(1));
	if (e != nullptr) {
		binder.pushusertype(e, "Entity", sizeof(Entity));
		return 1;
	}

	return 0;
		
}