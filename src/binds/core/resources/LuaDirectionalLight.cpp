#include "LuaDirectionalLight.h"

LuaDirectionalLight::LuaDirectionalLight()
{
}

LuaDirectionalLight::~LuaDirectionalLight()
{
}

const luaL_Reg LuaDirectionalLight::luaBinds_m[] = {
	{ "SetColor", lua_SetColor },
	{ "GetColor", lua_GetColor },
	{ "SetAmbience", lua_SetAmbience },
	{ "GetAmbience", lua_GetAmbience },
	{ "SetDiffuse", lua_SetDiffuse },
	{ "GetDiffuse", lua_GetDiffuse },
	{ "SetDirection", lua_SetDirection },
	{ "GetDirection", lua_GetDirection },
	{ NULL, NULL }
};

const luaL_Reg LuaDirectionalLight::luaBinds_f[] = {
	{ "new", lua_Create },
	{ "__gc", lua_Destroy },
	{NULL, NULL}
};

int LuaDirectionalLight::lua_Create(lua_State* L)
{
	LuaBinder binder(L);	
	DirectionalLight* light = new DirectionalLight();

	binder.pushusertype(light, "DirectionalLight", sizeof(DirectionalLight*));
	return 1;
}

int LuaDirectionalLight::lua_Destroy(lua_State* L)
{
	LuaBinder binder(L);
	DirectionalLight* light = (DirectionalLight*)binder.checkusertype(1, "DirectionalLight");
	delete light;
	return 0;
}

int LuaDirectionalLight::lua_SetColor(lua_State* L)
{
	LuaBinder binder(L);
	DirectionalLight* light = (DirectionalLight*)binder.checkusertype(1, "DirectionalLight");
	light->Color =** (static_cast<Vec3**>(binder.checkusertype(2, "Vec3")));

	Vec3* color =* (Vec3**)(binder.checkusertype(2, "Vec3"));
	return 0;
}

int LuaDirectionalLight::lua_GetColor(lua_State* L)
{
	LuaBinder binder(L);
	DirectionalLight* light = (DirectionalLight*)binder.checkusertype(1, "DirectionalLight");
	binder.pushusertype(&light->Color, "Vec3", sizeof(DirectionalLight));

	return 1;

}

int LuaDirectionalLight::lua_SetAmbience(lua_State* L)
{
	LuaBinder binder(L);
	DirectionalLight* light = (DirectionalLight*)binder.checkusertype(1, "DirectionalLight");
	light->AmbientIntensity = (float)binder.checknumber(2);

	return 0;
}

int LuaDirectionalLight::lua_GetAmbience(lua_State* L)
{
	LuaBinder binder(L);
	DirectionalLight* light = (DirectionalLight*)binder.checkusertype(1, "DirectionalLight");
	binder.pushnumber(light->AmbientIntensity);

	return 1;
}

int LuaDirectionalLight::lua_SetDiffuse(lua_State* L)
{
	LuaBinder binder(L);
	DirectionalLight* light = (DirectionalLight*)binder.checkusertype(1, "DirectionalLight");
	light->DiffuseIntensity = (float)binder.checknumber(2);

	return 0;

}

int LuaDirectionalLight::lua_GetDiffuse(lua_State* L)
{
	LuaBinder binder(L);
	DirectionalLight* light = (DirectionalLight*)binder.checkusertype(1, "DirectionalLight");
	binder.pushnumber(light->DiffuseIntensity);

	return 1;
}

int LuaDirectionalLight::lua_SetDirection(lua_State* L)
{
	LuaBinder binder(L);
	DirectionalLight* light = (DirectionalLight*)binder.checkusertype(1, "DirectionalLight");
	light->Direction =* *static_cast<glm::vec3**>(binder.checkusertype(2, "Vec3"));

	return 0;

}

int LuaDirectionalLight::lua_GetDirection(lua_State* L)
{
	LuaBinder binder(L);
	DirectionalLight* light = (DirectionalLight*)binder.checkusertype(1, "DirectionalLight");
	binder.pushusertype(&light->Direction, "Vec3", sizeof(DirectionalLight));

	return 1;

}