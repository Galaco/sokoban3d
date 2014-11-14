#ifndef LUAOBJECTBINDS_H
#define LUAOBJECTBINDS_H

#include <Lua.hpp>
#include <core/LuaBinder.h>


#include <binds/components/LuaCAnimation.h>
#include <binds/components/LuaCGraphics.h>
#include <binds/components/LuaCLuaScript.h>
#include <binds/core/components/LuaCTransform.h>
#include <binds/core/helpers/LuaKeyboard.h>
#include <binds/core/LuaEntity.h>
#include <binds/core/LuaCamera.h>
#include <binds/core/LuaState.h>
#include <binds/math/LuaVec3.h>

class LuaObjectBinds {
public:
	LuaObjectBinds(lua_State*);
	~LuaObjectBinds();

	void bindObjects();

private:
    lua_State* m_masterState;
};
#endif
