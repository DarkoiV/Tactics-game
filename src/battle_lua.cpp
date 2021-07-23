#include "battle_lua.hpp"

// Create new lua state
cBattleLua::cBattleLua(){
	L = luaL_newstate();
}

// Close lua state
cBattleLua::~cBattleLua(){
	lua_close(L);
}

// Get lua state
auto cBattleLua::operator()() -> lua_State*{
	return L;
}
