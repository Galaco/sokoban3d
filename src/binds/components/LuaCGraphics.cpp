#include "LuaCGraphics.h"

LuaCGraphics::LuaCGraphics(){}
LuaCGraphics::~LuaCGraphics(){}

const luaL_Reg LuaCGraphics::luaBinds_f[] = {
	{ "new", lua_Create },
	{ NULL, NULL }
};

const luaL_Reg LuaCGraphics::luaBinds_m[] = {
	{"GetModel", lua_GetModel},
	{"SetModel", lua_SetModel},
	{"AddModel", lua_AddModel},
	{"AddText", lua_AddText},
	{"AddMaterial", lua_AddMaterial},
	{"SetRenderMode", lua_SetRenderMode},
	{NULL, NULL}
};

int LuaCGraphics::lua_Create(lua_State* L)
{
	LuaBinder binder(L);
	CGraphics* v = new CGraphics();
	binder.pushusertype(v, "CGraphics", sizeof(CGraphics));
	return 1;
}

int LuaCGraphics::lua_GetModel(lua_State* L)
{
	LuaBinder binder(L);
	CGraphics* component = (CGraphics*)binder.checkusertype(1, "CGraphics");
	Model* v = component->getModel();
	binder.pushusertype(v, "Model", sizeof(Model));
	return 1;
}

int LuaCGraphics::lua_SetModel(lua_State* L)
{
	LuaBinder binder(L);
	CGraphics* component = (CGraphics*)binder.checkusertype(1, "CGraphics");

	component->setModel((Model*)binder.checkusertype(2, "Model") );
	return 0;
}

int LuaCGraphics::lua_AddModel(lua_State* L)
{
	LuaBinder binder(L);
	CGraphics* component =* (CGraphics**)binder.checkusertype(1, "CGraphics");

	component->addModel(binder.checkstring(2));
	return 0;
}

int LuaCGraphics::lua_SetRenderMode(lua_State* L)
{
	LuaBinder binder(L);
	CGraphics* component =* (CGraphics**)binder.checkusertype(1, "CGraphics");
	unsigned int mode = RENDER_MODE_3D;
	std::string mo = binder.checkstring(2);
	if (mo == "RENDER_2D")
	{
		mode = RENDER_MODE_2D;
	}

	component->setRenderMode(mode);
	return 0;
}

int LuaCGraphics::lua_AddText(lua_State* L)
{
	LuaBinder binder(L);
	CGraphics* component = (CGraphics*)binder.checkusertype(1, "CGraphics");
	component->addText(binder.checkstring(2), binder.checknumber(3));
	return 0;
}

int LuaCGraphics::lua_AddMaterial(lua_State* L)
{
	LuaBinder binder(L);
	CGraphics* component =* (CGraphics**)binder.checkusertype(1, "CGraphics");
	component->addMaterial(binder.checkstring(2));
	return 0;
}