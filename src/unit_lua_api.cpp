#include "unit.hpp"
#include "struct_tagged.hpp"

// Push tagged unit on Lua stack
void cUnit::pushTaggedUnit(lua_State *L, cUnit* pointer) {
	sTagged* taggedUnit = (sTagged*)lua_newuserdatauv(L, sizeof(sTagged), 0);
	taggedUnit->pointer = pointer;
	taggedUnit->tag = eTAG::UNIT;

	luaL_getmetatable(L, "UnitMetatable");
	if( not lua_istable(L, -1) ) {
		std::cout << "[ERROR] Could not set unit metatable " << std::endl;
		return;
	}
	
	lua_setmetatable(L, -2);
}

// Get unit pointer from tagged container
auto cUnit::getTaggedUnit(lua_State *L, int indx) -> cUnit* {	
	if(lua_type(L, indx) != LUA_TUSERDATA) {
		std::cout << "[ERROR][LUA API] Not a user data" << std::endl;
		return nullptr;
	}

	sTagged *taggedPointer = (sTagged*)lua_touserdata(L, indx);
	if(taggedPointer->tag != eTAG::UNIT) {
		std::cout << "[ERROR][LUA API] Wrong pointer type" << std::endl;
		return nullptr;
	}

	return (cUnit*)taggedPointer->pointer;
}

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

	lua_pushcfunction(L, l_getFirstItem);
	lua_setfield(L, -2, "getItem");

	lua_pushcfunction(L, l_getPhysical);
	lua_setfield(L, -2, "getPhysical");

	lua_pushcfunction(L, l_getHP);
	lua_setfield(L, -2, "getHP");

	lua_pushcfunction(L, l_damage);
	lua_setfield(L, -2, "damage");

	lua_pushcfunction(L, l_heal);
	lua_setfield(L, -2, "heal");

	// Create metatable and register functions
	luaL_newmetatable(L, "UnitMetatable");
	lua_pushvalue(L, tableIndex);
	lua_setfield(L, -2, "__index");

	// Clean stack
	lua_pop(L, -1);
}

// Get unit pos in lua
int cUnit::l_getPos(lua_State *L) {
	// Takes unit as argument
	cUnit *unit;

	// Get unit from lua stack
	unit = cUnit::getTaggedUnit(L, -1);
	if(unit == nullptr) return 0;

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

	// Get unit from lua stack
	unit = cUnit::getTaggedUnit(L, -3);
	if(unit == nullptr) return 0;

	if(not lua_isnumber(L, -2) or not lua_isnumber(L, -1)) {
		std::cout << "[ERROR][LUA API] Function needs 2 numbers which were not provided" << std::endl;
		return 0;
	}
	x = (int)lua_tointeger(L, -2);
	y = (int)lua_tointeger(L, -1);

	vec2D offset{x, y};

	unit->offsetPosition(offset);

	return 0;
}

// Reset offset
int cUnit::l_resetOffset(lua_State *L) {
	// Takes unit as argument
	cUnit* unit;
	
	// Get unit from lua stack
	unit = cUnit::getTaggedUnit(L, -1);
	if(unit == nullptr) return 0;

	unit->resetOffset();

	return 0;
}

// Get first item in inventory(nil if none)
int cUnit::l_getFirstItem(lua_State *L) {
	// Takes unit as argument
	cUnit* unit;

	// Get unit from lua stack
	unit = cUnit::getTaggedUnit(L, -1);
	if (unit == nullptr) return 0;

	// Get first item in inventory, and check if exists
	auto item = unit->inventory().getFirstItem();
	if (item == nullptr) {
		lua_pushnil(L);
		return 1;
	}

	// Pass id of first item
	auto itemID = item->getID();
	lua_getglobal(L, itemID.c_str());
	return 1;
}

// Get STR and DEF
int cUnit::l_getPhysical(lua_State *L) {
	// Takes unit as argument
	cUnit* unit;

	// Get unit from lua stack
	unit = cUnit::getTaggedUnit(L, -1);
	if(unit == nullptr) return 0;

	//Returns STR and DEG
	int STR, DEF;
	STR = unit->m_stats.STR;
	DEF = unit->m_stats.DEF;
	
	lua_pushnumber(L, STR);
	lua_pushnumber(L, DEF);

	return 2;
}

// Get HP
int cUnit::l_getHP(lua_State *L) {
	// Takes unit as argument
	cUnit* unit;

	// Get unit from lua stack
	unit = cUnit::getTaggedUnit(L, -1);
	if (unit == nullptr) return 0;

	int hp = unit->getStats().HP;
	lua_pushnumber(L, hp);

	return 1;
}

// Deal damage to unit from LUA
int cUnit::l_damage(lua_State *L) {
	// Takes unit, and amount of damage as arguments
	cUnit* unit;
	int damage;

	// Get unit from lua stack
	unit = cUnit::getTaggedUnit(L, -2);
	if(unit == nullptr) return 0;

	if (not lua_isnumber(L, -1)) {
		std::cout << "[ERROR][LUA API] Function needs number, which were not provided" << std::endl;
		return 0;
	}

	damage = (int)lua_tonumber(L, -1);
	
	// Deal damage
	if(unit->m_stats.HP > damage)
		unit->m_stats.HP -= damage;
	else
		unit->m_stats.HP = 0;

	return 0;
}

// Heal unit from LUA
int cUnit::l_heal(lua_State *L) {
	// Takes unit, and amount of heal as arguments
	cUnit* unit;
	int healAmount;

	// Get unit from lua stack
	unit = cUnit::getTaggedUnit(L, -2);
	if(unit == nullptr) return 0;

	if (not lua_isnumber(L, -1)) {
		std::cout << "[ERROR][LUA API] Function needs number, which were not provided" << std::endl;
		return 0;
	}

	healAmount = (int)lua_tonumber(L, -1);
	unit->heal(healAmount);

	return 0;
}
