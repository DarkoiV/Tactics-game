#include "unit.hpp"

// Create unit table, and register functions
void cUnit::registerUnitApi(lua_State *L) {
	// Create Unit table
	lua_newtable(L);
	int tableIndex = lua_gettop(L);
	lua_pushvalue(L, tableIndex);
	lua_setglobal(L, "Unit");

	lua_pushcfunction(L, l_getPos);
	lua_setfield(L, -2, "getPos");

	lua_pushcfunction(L, l_offset);
	lua_setfield(L, -2, "offset");

	lua_pushcfunction(L, l_resetOffset);
	lua_setfield(L, -2, "resetOffset");

	lua_pushcfunction(L, l_damage);
	lua_setfield(L, -2, "damage");
}

// Get unit pos in lua
int cUnit::l_getPos(lua_State *L) {
	// Takes unit as argument
	cUnit *unit;

	if(lua_type(L, -1) != LUA_TLIGHTUSERDATA) {
		std::cout << "[ERROR][LUA API] Not a pointer to unit" << std::endl;
		return 0;
	}

	unit = (cUnit*)lua_topointer(L, -1);

	// Returns x, y
	vec2D pos = unit->getPosition();
	lua_pushnumber(L, pos.x);
	lua_pushnumber(L, pos.y);

	return 2;
}

// Offset unit from LUA
int cUnit::l_offset(lua_State *L) {
	// Takes unit, and {x, y} as argument
	cUnit* unit;
	int x, y;

	if(lua_type(L, -3) != LUA_TLIGHTUSERDATA) {
		std::cout << "[ERROR][LUA API] Not a pointer to unit" << std::endl;
		return 0;
	}

	unit = (cUnit*)lua_topointer(L, -3);

	if(not lua_isnumber(L, -2) or not lua_isnumber(L, -1)) {
		std::cout << "[ERROR][LUA API] Function needs 2 integers which were not provided" << std::endl;
		return 0;
	}
	x = (int)lua_tonumber(L, -2);
	y = (int)lua_tonumber(L, -1);

	vec2D offset{x, y};

	unit->offsetPosition(offset);

	return 0;
}

// Reset offset
int cUnit::l_resetOffset(lua_State *L) {
	// Takes unit as argument
	cUnit* unit;
	
	if(lua_type(L, -1) != LUA_TLIGHTUSERDATA) {
		std::cout << "[ERROR][LUA API] Not a pointer to unit" << std::endl;
		return 0;
	}

	unit = (cUnit*)lua_topointer(L, -1);
	unit->resetOffset();

	return 0;
}

// Deal damage to unit from LUA
int cUnit::l_damage(lua_State *L) {

	return 0;
}
