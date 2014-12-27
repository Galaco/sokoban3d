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


	/*  \ */
	binder.initialize("Game", NULL, LuaGame::luaBinds_f, LuaGame::luaBinds_m);

	/*	\components */
	binder.initialize("CAnimation", "Component", LuaCAnimation::luaBinds_f, LuaCAnimation::luaBinds_m);
	binder.initialize("CGraphics", "Component", LuaCGraphics::luaBinds_f, LuaCGraphics::luaBinds_m);
	binder.initialize("CScript", "Component", LuaCLuaScript::luaBinds_f, LuaCLuaScript::luaBinds_m);
	binder.initialize("CCollision", "Component", LuaCCollision::luaBinds_f, LuaCCollision::luaBinds_m);
	binder.initialize("CSelectable", "Component", LuaCSelectable::luaBinds_f, LuaCSelectable::luaBinds_m);

	/*	\core */
	binder.initialize("Camera", NULL, LuaCamera::luaBinds_f, LuaCamera::luaBinds_m);
	binder.initialize("Entity", NULL, LuaEntity::luaBinds_f, LuaEntity::luaBinds_m);
	binder.initialize("State", NULL, LuaState::luaBinds_f, LuaState::luaBinds_m);

	/*	\core\components */
	binder.initialize("Transform", NULL, LuaCTransform::luaBinds_f, LuaCTransform::luaBinds_m);

	/*	\core\helpers */
	binder.initialize("Keyboard", NULL, LuaKeyboard::luaBinds_f, LuaKeyboard::luaBinds_m);
	binder.initialize("Mouse", NULL, LuaMouse::luaBinds_f, LuaMouse::luaBinds_m);

	/*	\core\resources */
	binder.initialize("DirectionalLight", NULL, LuaDirectionalLight::luaBinds_f, LuaDirectionalLight::luaBinds_m);
	binder.initialize("LuaScript", NULL, LuaLuaScript::luaBinds_f, LuaLuaScript::luaBinds_m);
	binder.initialize("PointLight", NULL, LuaPointLight::luaBinds_f, LuaPointLight::luaBinds_m);
	binder.initialize("Text", NULL, LuaText::luaBinds_f, LuaText::luaBinds_m);



	/*	\math */
	binder.initialize("Vec3", NULL, LuaVec3::luaBinds_f, LuaVec3::luaBinds_m);
}