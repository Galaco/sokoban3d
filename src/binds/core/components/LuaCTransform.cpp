#include "LuaCTransform.h"

LuaCTransform::LuaCTransform() {
}

LuaCTransform::~LuaCTransform(){
}

const luaL_Reg LuaCTransform::luaBinds_f[] = {
	{ "new", lua_Create },
	{ NULL, NULL }
};

const luaL_Reg LuaCTransform::luaBinds_m[] = {
	{"GetPosition", lua_GetPosition},
	{"SetPosition", lua_SetPosition},
	{"GetOrientation", lua_GetOrientation},
	{"SetOrientation", lua_SetOrientation},
	{"GetScale", lua_GetScale},
	{"SetScale", lua_SetScale},
	{NULL, NULL}
};

int LuaCTransform::lua_Create(lua_State* L)
{
	LuaBinder binder(L);
	CTransform* v = new CTransform();
	binder.pushusertype(v, "Transform", sizeof(CTransform));
	return 1;
}
int LuaCTransform::lua_GetPosition(lua_State* L)
{
	LuaBinder binder(L);
	CTransform* component = (CTransform*)binder.checkusertype(1, "Transform");
	Vec3* v = &static_cast<Vec3>(component->getPosition());

	binder.pushusertype(v, "Vec3", sizeof(Vec3));
	return 1;
}
int LuaCTransform::lua_SetPosition(lua_State* L)
{
	LuaBinder binder(L);
	CTransform* component = (CTransform*)binder.checkusertype(1, "Transform");

	component->setPosition(**(Vec3**)binder.checkusertype(2, "Vec3"));
	return 0;
}
int LuaCTransform::lua_GetOrientation(lua_State* L)
{
	LuaBinder binder(L);
	CTransform* component = (CTransform*)binder.checkusertype(1, "Transform");
	Vec3* v = &static_cast<Vec3>(component->getOrientation());
	binder.pushusertype(v, "Vec3", sizeof(Vec3));
	return 1;
}
int LuaCTransform::lua_SetOrientation(lua_State* L)
{
	LuaBinder binder(L);
	CTransform* component = (CTransform*)binder.checkusertype(1, "Transform");

	component->setOrientation(**(Vec3**)binder.checkusertype(2, "Vec3") );
	return 0;
}
int LuaCTransform::lua_GetScale(lua_State* L)
{
	LuaBinder binder(L);
	CTransform* component = (CTransform*)binder.checkusertype(1, "Transform");
	Vec3* v = &static_cast<Vec3>(component->getScale());
	binder.pushusertype(v, "Vec3", sizeof(Vec3));
	return 1;
}
int LuaCTransform::lua_SetScale(lua_State* L)
{
	LuaBinder binder(L);
	CTransform* component = (CTransform*)binder.checkusertype(1, "Transform");

	component->setScale(*(Vec3*)binder.checkusertype(2, "Vec3") );
	return 0;
}