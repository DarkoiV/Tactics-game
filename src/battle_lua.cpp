#include "battle_lua.hpp"
#include "globals.hpp"

// Create new lua state
cBattleLua::cBattleLua(){
	L = luaL_newstate();

	// Open libs
	luaL_openlibs(L);

	// Do files needed for scene battle
	std::string weaponsFile = g_basePath + "data/battle_includes.lua";
	luaL_dofile(L, weaponsFile.c_str());
}

// Close lua state
cBattleLua::~cBattleLua(){
	lua_close(L);
}

// Get lua state
auto cBattleLua::operator()() -> lua_State*{
	return L;
}
