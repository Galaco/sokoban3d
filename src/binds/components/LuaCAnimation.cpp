#include "LuaCAnimation.h"

LuaCAnimation::LuaCAnimation(){}
LuaCAnimation::~LuaCAnimation(){}

const luaL_Reg LuaCAnimation::luaBinds[] = {
	{"Create", lua_Create},
	{"SetAnimation", lua_SetAnimation},
	{"GetAnimation", lua_GetAnimation},
	{"AddAnimation", lua_AddAnimation},
	{NULL, NULL}
};

int LuaCAnimation::lua_Create(lua_State* L)
{
	LuaBinder binder(L);
	CAnimation* v = new CAnimation();
	binder.pushusertype(v, "CGraphics");
	return 1;
}
int LuaCAnimation::lua_GetAnimation(lua_State* L)
{
	LuaBinder binder(L);
	CAnimation* component = (CAnimation*)binder.checkusertype(1, "CAnimation");
	BaseAnimation* v = component->getAnimation();
	binder.pushusertype(v, "BaseAnimation");
	return 1;
}
int LuaCAnimation::lua_SetAnimation(lua_State* L)
{
	LuaBinder binder(L);
	CAnimation* component = (CAnimation*)binder.checkusertype(1, "CAnimation");

	component->setAnimation((BaseAnimation*)binder.checkusertype(2, "BaseAnimation") );
	return 0;
}

int LuaCAnimation::lua_AddAnimation(lua_State* L)
{
	LuaBinder binder(L);
	CAnimation* component = (CAnimation*)binder.checkusertype(1, "CAnimation");

	component->addAnimation(binder.checkstring(2));
	return 0;
}