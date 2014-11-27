#include "LuaScript.h"


lua_State* LuaScript::m_masterLuaState = nullptr;

LuaScript::LuaScript(lua_State* s){
	if (m_masterLuaState == nullptr) {
		m_masterLuaState = s;
	}

	threadState = lua_newthread(s);
	lua_pushlightuserdata(s, threadState);
	lua_pushlightuserdata(s, this);
	//lua_settable(s, LUA_RIDX_GLOBALS);

	state = LSS_NOTLOADED;
	time = 0.f;
	waitTimestamp = 0.f;
	waitFrame = 0;
}

LuaScript::~LuaScript(){
	m_masterLuaState = nullptr;
}

void LuaScript::runString(const char*){

}

void LuaScript::runFile(std::string fileName, std::string global, bool autorun){
	assert(m_masterLuaState);
	assert(threadState);
	FILE* fp = fopen(("scripts/" + fileName).c_str(), "rt");
	if(!fp){
		return;
	}

	std::vector<std::string> sLines;
	char sLine[255];
	while(fgets(sLine, 255, fp))sLines.push_back(sLine);
	fclose(fp);

	std::string max = "";
	for(int i =0; i<(int)sLines.size(); i++){
		max = max + sLines[i];
	}


	const char* rawScript = max.c_str();

	status = luaL_loadstring( threadState, rawScript );
	if (status == 0){
		if (global != "") {
			m_environmentId = global;
			lua_getglobal(threadState, global.c_str());
			lua_setupvalue(threadState, -2, 1);
		}
		if (autorun){
			resumeScript(0.0f);
		}
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
		//FormatError();
		//OutputError("Runtime Error:");
	}
}

void LuaScript::handleError(){
	const char* msg;

	msg = lua_tostring(threadState, -1);
	if (msg == NULL)
		msg = "(error with no message)";
	lua_pop(threadState, 1);
	m_Logger->log(WARNING, "Lua Error:");
	m_Logger->log(WARNING, msg);
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
		break;
		//        case LSS_DONE:
	default :
		// if we aren't waiting and we get here, the script must be done
		//            if (autoDelete)
		//                {
		//                LUASCRIPT*  sNext;
		//
		//                sNext = next;
		//                delete(this);
		//                return(sNext);
		//                }
		callFn("Update", 0);
		break;
	}
}


void LuaScript::callFunction(const char* funcName){
	callFn(funcName, 0);
}

void LuaScript::callFn(const char* fnName, int iParam){
	int         status;

	// find the lua function and push it on the stack
	lua_getglobal (threadState, fnName);

	// push our single argument
	lua_pushnumber(threadState, iParam);

	// now, call into Lua
	status = lua_pcall(threadState, 1, 0, 0);

	if (status){
		handleError();
	}
}