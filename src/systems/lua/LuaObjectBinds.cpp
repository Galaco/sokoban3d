#include "LuaObjectBinds.h"

LuaObjectBinds::LuaObjectBinds(lua_State* L){
    m_masterState = L;
}

LuaObjectBinds::~LuaObjectBinds(){
    m_masterState = nullptr;
}

void LuaObjectBinds::bindObjects(){
    LuaBinder binder(m_masterState);

	/*	\components */
	binder.initialize("CAnimation", LuaCAnimation::luaBinds);
	binder.initialize("CGraphics", LuaCGraphics::luaBinds);
	binder.initialize("CScript", LuaCLuaScript::luaBinds);

	/*	\core */
	binder.initialize("Camera", LuaCamera::luaBinds);
	binder.initialize("Entity", LuaEntity::luaBinds);
	binder.initialize("State", LuaState::luaBinds);

	/*	\core\components */
	binder.initialize("Transform", LuaCTransform::luaBinds);

	/*	\core\helpers */
	binder.initialize("Keyboard", LuaKeyboard::luaBinds);



	/*	\math */
	binder.initialize("Vec3", LuaVec3::luaBinds);
}