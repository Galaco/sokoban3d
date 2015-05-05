#include "LuaObjectBinds.h"

LuaObjectBinds::LuaObjectBinds(){
}

void LuaObjectBinds::setLuaState(lua_State* L){
	m_masterState = L;
}

LuaObjectBinds::LuaObjectBinds(lua_State* L){
    m_masterState = L;
}

LuaObjectBinds::~LuaObjectBinds(){
    m_masterState = nullptr;
}

void LuaObjectBinds::bindObjects(){
    LuaBinder binder(m_masterState);

	// This simply binds all the luaBinds in each Lua class included
	/*  \ */
	binder.initialize("Game", LuaGame::luaBinds);

	/*	\components */
	binder.initialize("CAnimation", LuaCAnimation::luaBinds);
	binder.initialize("CGraphics", LuaCGraphics::luaBinds);
	binder.initialize("CScript", LuaCLuaScript::luaBinds);
	binder.initialize("CCollision", LuaCCollision::luaBinds);
	binder.initialize("CSelectable", LuaCSelectable::luaBinds);

	/*	\core */
	binder.initialize("Camera", LuaCamera::luaBinds);
	binder.initialize("Entity", LuaEntity::luaBinds);
	binder.initialize("State", LuaState::luaBinds);

	/*	\core\components */
	binder.initialize("Transform", LuaCTransform::luaBinds);

	/*	\core\helpers */
	binder.initialize("Keyboard", LuaKeyboard::luaBinds);
	binder.initialize("Mouse", LuaMouse::luaBinds);

	/*	\core\resources */
	binder.initialize("DirectionalLight", LuaDirectionalLight::luaBinds);
	binder.initialize("LuaScript", LuaLuaScript::luaBinds);
	binder.initialize("PointLight", LuaPointLight::luaBinds);
	binder.initialize("Text", LuaText::luaBinds);


	/*	\game */
	binder.initialize("SOKOBAN", LuaSokoban::luaBinds);

	/*	\math */
	binder.initialize("Vec3", LuaVec3::luaBinds);
}