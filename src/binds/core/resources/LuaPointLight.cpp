#include "LuaPointLight.h"

LuaPointLight::LuaPointLight()
{
}

LuaPointLight::~LuaPointLight()
{
}

const luaL_Reg LuaPointLight::luaBinds[] = {
	{ "Create", lua_Create },
	{ "Destroy", lua_Destroy },
	{ "SetColor", lua_SetColor },
	{ "GetColor", lua_GetColor },
	{ "SetAmbience", lua_SetAmbience },
	{ "GetAmbience", lua_GetAmbience },
	{ "SetDiffuse", lua_SetDiffuse },
	{ "GetDiffuse", lua_GetDiffuse },
	{ "SetPosition", lua_SetPosition },
	{ "GetPosition", lua_GetPosition },
	{ NULL, NULL }
};

int LuaPointLight::lua_Create(lua_State* L)
{
	LuaBinder binder(L);
	PointLight* light = new PointLight();

	binder.pushusertype(light, "PointLight");
	return 1;
}

int LuaPointLight::lua_Destroy(lua_State* L)
{
	LuaBinder binder(L);
	PointLight* light = (PointLight*)binder.checkusertype(1, "PointLight");
	delete light;
	return 0;
}

int LuaPointLight::lua_SetColor(lua_State* L)
{
	LuaBinder binder(L);
	PointLight* light = (PointLight*)binder.checkusertype(1, "PointLight");
	light->setColor(*static_cast<glm::vec3*>(binder.checkusertype(2, "Vec3")));

	return 0;

}

int LuaPointLight::lua_GetColor(lua_State* L)
{
	LuaBinder binder(L);
	PointLight* light = (PointLight*)binder.checkusertype(1, "PointLight");
	binder.pushusertype(&light->getColor(), "Vec3");

	return 1;

}

int LuaPointLight::lua_SetAmbience(lua_State* L)
{
	LuaBinder binder(L);
	PointLight* light = (PointLight*)binder.checkusertype(1, "PointLight");
	light->setAmbience((float)binder.checknumber(2));

	return 0;
}

int LuaPointLight::lua_GetAmbience(lua_State* L)
{
	LuaBinder binder(L);
	PointLight* light = (PointLight*)binder.checkusertype(1, "PointLight");
	binder.pushnumber(light->getAmbience());

	return 1;
}

int LuaPointLight::lua_SetDiffuse(lua_State* L)
{
	LuaBinder binder(L);
	PointLight* light = (PointLight*)binder.checkusertype(1, "PointLight");
	light->setDiffuse((float)binder.checknumber(2));

	return 0;

}

int LuaPointLight::lua_GetDiffuse(lua_State* L)
{
	LuaBinder binder(L);
	PointLight* light = (PointLight*)binder.checkusertype(1, "PointLight");
	binder.pushnumber(light->getDiffuse());

	return 1;
}


int LuaPointLight::lua_SetPosition(lua_State* L)
{
	LuaBinder binder(L);
	PointLight* light = (PointLight*)binder.checkusertype(1, "PointLight");
	light->setPosition(*static_cast<glm::vec3*>(binder.checkusertype(2, "Vec3")));

	return 0;
}

int LuaPointLight::lua_GetPosition(lua_State* L)
{
	LuaBinder binder(L);
	PointLight* light = (PointLight*)binder.checkusertype(1, "PointLight");
	binder.pushusertype(&light->getPosition(), "Vec3");

	return 1;
}