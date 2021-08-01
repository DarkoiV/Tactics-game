#include "unit.hpp"

// Get unit pos in lua
int cUnit::l_getUnitPos(lua_State *L) {
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
int cUnit::l_offsetUnit(lua_State *L) {
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

// Deal damage to unit from LUA
int cUnit::l_dealDamage(lua_State *L) {

	return 0;
}
