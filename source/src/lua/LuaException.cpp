#include "LuaException.h"

lua_exception::lua_exception(struct lua_State *L, struct lua_longjmp
	*errorJmp)
	:L(L)
	, errorJmp(errorJmp)
	, committed(false)
{
}

const char *lua_exception::what() const
{
	// Look! You can inspect the error message using a standard call!
	return lua_tostring(L, -1);
}

lua_exception::~lua_exception()
{
	if (!committed)
	{
		// The exception was caught before Lua got it.
		// Revert the error state
		// TODO: Is it safe to set it to 0 or should we
		// restore it to a previous state?
		//errorJmp->status = 0;
		// Pop the error message
		lua_pop(L, 1);
	}
}