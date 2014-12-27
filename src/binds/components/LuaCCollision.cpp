#include "LuaCCollision.h"

LuaCCollision::LuaCCollision(){}
LuaCCollision::~LuaCCollision(){}

const luaL_Reg LuaCCollision::luaBinds_f[] = {
	{ "new", lua_Create },
	{ NULL, NULL }
};

const luaL_Reg LuaCCollision::luaBinds_m[] = {
	{ "BuildCollisionMesh", lua_CreateCollisionModel },
	{NULL, NULL}
};

int LuaCCollision::lua_Create(lua_State* L)
{
	LuaBinder binder(L);
	CCollision* v = new CCollision();
	binder.pushusertype(v, "CCollision", sizeof(CCollision));
	return 1;
}

int LuaCCollision::lua_CreateCollisionModel(lua_State* L)
{
	LuaBinder binder(L);
	CCollision* v = static_cast<CCollision*>(binder.checkusertype(1, "CCollision"));
	if (!v->getOwner())
	{
		return 0;
	}

	std::vector<Component*> c = v->getOwner()->getComponentsByType("Graphics");
	if (c.size() < 1)
	{
		return 0;
	}

	v->rebuildCollisionBox(static_cast<CGraphics*>(c[0])->getModel());
	return 0;
}