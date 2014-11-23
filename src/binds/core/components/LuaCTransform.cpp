#include "LuaCTransform.h"

LuaCTransform::LuaCTransform() {
}

LuaCTransform::~LuaCTransform(){
}

const luaL_Reg LuaCTransform::luaBinds[] = {
	{"Create", lua_Create},
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
	binder.pushusertype(v, "Transform");
	return 1;
}
int LuaCTransform::lua_GetPosition(lua_State* L)
{
	LuaBinder binder(L);
	CTransform* component = (CTransform*)binder.checkusertype(1, "Transform");
	glm::vec3* v = &component->getPosition();
	binder.pushusertype(v, "position");
	return 1;
}
int LuaCTransform::lua_SetPosition(lua_State* L)
{
	LuaBinder binder(L);
	CTransform* component = (CTransform*)binder.checkusertype(1, "Transform");

	component->setPosition(*(Vec3*)binder.checkusertype(2, "Vector3d") );
	return 0;
}
int LuaCTransform::lua_GetOrientation(lua_State* L)
{
	LuaBinder binder(L);
	CTransform* component = (CTransform*)binder.checkusertype(1, "Transform");
	glm::vec3* v = &component->getOrientation();
	binder.pushusertype(v, "orientation");
	return 1;
}
int LuaCTransform::lua_SetOrientation(lua_State* L)
{
	LuaBinder binder(L);
	CTransform* component = (CTransform*)binder.checkusertype(1, "Transform");

	component->setOrientation(*(Vec3*)binder.checkusertype(2, "Vector3d") );
	return 0;
}
int LuaCTransform::lua_GetScale(lua_State* L)
{
	LuaBinder binder(L);
	CTransform* component = (CTransform*)binder.checkusertype(1, "Transform");
	glm::vec3* v = &component->getScale();
	binder.pushusertype(v, "scale");
	return 1;
}
int LuaCTransform::lua_SetScale(lua_State* L)
{
	LuaBinder binder(L);
	CTransform* component = (CTransform*)binder.checkusertype(1, "Transform");

	component->setScale(*(Vec3*)binder.checkusertype(2, "Vector3d") );
	return 0;
}