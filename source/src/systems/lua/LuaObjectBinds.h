/*********************************************************************
Project: Dissertation
Author: Josh Martin

Name: Lua Object Binds
Description: Pushes lua bindings to the global table of the lua stack.
			 Bindings pushed are accessible in lua script.
*********************************************************************/
#ifndef LUAOBJECTBINDS_H
#define LUAOBJECTBINDS_H

#include <Lua.hpp>
#include <core/LuaBinder.h>

#include <binds\LuaGame.h>

#include <binds/components/LuaCAnimation.h>
#include <binds/components/LuaCGraphics.h>
#include <binds/components/LuaCLuaScript.h>
#include <binds/components/LuaCCollision.h>
#include <binds/components/LuaCSelectable.h>

#include <binds/core/components/LuaCTransform.h>
#include <binds/core/helpers/LuaKeyboard.h>
#include <binds/core/helpers/LuaMouse.h>
#include <binds/core/resources/LuaDirectionalLight.h>
#include <binds/core/resources/LuaLuaScript.h>
#include <binds/core/resources/LuaPointLight.h>
#include <binds/core/resources/LuaText.h>

#include <binds/core/LuaEntity.h>
#include <binds/core/LuaCamera.h>
#include <binds/core/LuaState.h>
#include <binds/math/LuaVec3.h>

#include <binds/GAME/LuaSOKOBAN.h>

class LuaObjectBinds {
public:
	LuaObjectBinds();
	LuaObjectBinds(lua_State*);
	~LuaObjectBinds();

	void setLuaState(lua_State* L);

	void bindObjects();

private:
    lua_State* m_masterState;
};
#endif
