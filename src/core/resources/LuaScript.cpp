#include "LuaScript.h"


lua_State* LuaScript::m_masterLuaState;

LuaScript::LuaScript(){
	state = LSS_NOTLOADED;
	time = 0.f;
	waitTimestamp = 0.f;
	waitFrame = 0;
}

LuaScript::LuaScript(lua_State* s){
	if (!m_masterLuaState) {
		m_masterLuaState = s;
	}

	m_controlState = s;

	threadState = lua_newthread(m_masterLuaState);
	//lua_pushlightuserdata(s, threadState);
	//lua_pushlightuserdata(s, this);

	state = LSS_NOTLOADED;
	time = 0.f;
	waitTimestamp = 0.f;
	waitFrame = 0;
}

void LuaScript::prepare(lua_State* s){
	if (!m_masterLuaState) {
		m_masterLuaState = s;
	}
	m_controlState = s;

	if (!threadState)
		threadState = lua_newthread(m_masterLuaState);
	//lua_pushlightuserdata(s, threadState);
	//lua_pushlightuserdata(s, this);
}

LuaScript::~LuaScript(){
}

void LuaScript::runString(const char*){

}

void LuaScript::runFile(std::string fileName, std::string globalName){
	assert(m_masterLuaState);
	assert(threadState);
	FILE* fp = fopen(("scripts/" + fileName).c_str(), "rt");
	if(!fp) return;

	std::vector<std::string> sLines;
	char sLine[255];
	while(fgets(sLine, 255, fp))sLines.push_back(sLine);
	fclose(fp);

	std::string max = "";
	for(int i =0; i<(int)sLines.size(); i++){
		max = max + sLines[i];
	}

	if (globalName != "")
	{
		std::string whiteList(
			"print = print,"
			"os = os,"
			"dofile = dofile,"
			"string = string,"
			"Mouse = Mouse,"
			"Keyboard = Keyboard,"
			"Entity = Entity,"
			"Transform = Transform,"
			"Vec3 = Vec3,"
			"Game = Game,"
			"State = State,"
			"Camera = Camera"
		);

		std::string lua_sandbox(
			globalName + " = { " + whiteList + " }  "
			"_ENV = " + globalName + " "
		);
		max = lua_sandbox + max;

		m_environmentId = globalName;
	}

	const char* rawScript = max.c_str();

	status = luaL_loadstring(threadState, rawScript);
	if (status == 0){
		resumeScript(0.0f);
	} else {
		handleError();
	}
}


void LuaScript::resumeScript(float param){
	state  = LSS_RUNNING;
	lua_pushnumber(threadState, param);

	status = lua_resume(threadState, NULL, 1);
	if (status)
	{
		handleError();
	}
}

void LuaScript::update(float dt){
	time += dt;
	switch(state)
	{
	case LSS_WAITTIME:
		if (time >= waitTimestamp)
			resumeScript(0.0f);
		break;
	case LSS_WAITFRAME:
		waitFrame--;
		if (waitFrame <= 0)
			resumeScript(0.0f);
		break;
	case LSS_NOTLOADED:
		return;
		break;
	default :
		callFn("Update", 0);
		break;
	}
}


void LuaScript::callFunction(const char* funcName){
	callFn(funcName, 0);
}

void LuaScript::callFn(const char* fnName, int iParam){
	int         status = 0;

	// find the lua function and push it on the stack
	try{
		assert(threadState);
		if (m_environmentId.c_str())
		{
			lua_getglobal(threadState, m_environmentId.c_str());
			if (!lua_istable(threadState, 1)) return;
			lua_getfield(threadState, -1, fnName);
		}
		else {
			lua_getglobal(threadState, fnName);
			if (!lua_istable(threadState, 1)) return;
		}
	}
	catch (const std::exception& e)
	{
		char error_buf[1024];
		std::strncpy(error_buf, "Unhandled exception in Lua hook", sizeof(error_buf));
		Logger::log(ERROR_, std::string(error_buf).c_str());
		e.what();

		luaL_error(threadState, "%s", error_buf);
		return;
	}

	// now, call into Lua
	try {
		// push our single argument
		//lua_pushnumber(threadState, iParam);

		if (0 != lua_pcall(threadState, 0, 0, 0)){
			handleError();
		}
	}
	catch (const std::exception& e)
	{
		e.what();
	}
}

void LuaScript::handleError(){
	const char* msg;

	msg = lua_tostring(threadState, -1);
	if (msg == NULL)
		msg = "Error with no message";
	lua_pop(threadState, 1);
	Logger::log(WARNING, "Lua Error:");
	Logger::log(WARNING, msg);
}