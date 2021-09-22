#include "item.hpp"

auto cItem::newItem(const std::string& p_id, cBattleLua& Lua) -> cItem{
	cItem item;

	// On failure item id will be empty
	item.m_id = "";

	// Find item table
	lua_getglobal(Lua(), p_id.c_str());
	if(not lua_istable(Lua(), -1)) {
		std::cout << "[ERROR] No item with id " << p_id << std::endl;
		return item;
	}

	// Get item name
	lua_getfield(Lua(), -1, "name");
	if(not lua_isstring(Lua(), -1)) {
		std::cout << "[ERROR] no item name in " << p_id << std::endl;
		return item;
	}
	item.m_name = lua_tostring(Lua(), -1);
	lua_pop(Lua(), 1);

	// Get ranges
	lua_getfield(Lua(), -1, "minRange");
	if(not lua_isnumber(Lua(), -1)) {
		std::cout << "[ERROR] no min range value in item " << p_id << std::endl;
		return item;
	}
	item.m_minRange = (int)lua_tonumber(Lua(), -1);
	lua_pop(Lua(), 1);

	lua_getfield(Lua(), -1, "maxRange");
	if(not lua_isnumber(Lua(), -1)) {
		std::cout << "[ERROR] no max range value in item " << p_id << std::endl;
		return item;
	}
	item.m_maxRange = (int)lua_tonumber(Lua(), -1);
	lua_pop(Lua(), 1);

	// Get type of item
	lua_getfield(Lua(), -1, "iType");
	if(not lua_isnumber(Lua(), -1)) {
		std::cout << "[ERROR] No item type " << p_id << std::endl;
		return item;
	}
	item.m_type = (eITEM)lua_tonumber(Lua(), -1);
	lua_pop(Lua(), 1);

	// Get action of item
	lua_getfield(Lua(), -1, "action");
	if(not lua_isstring(Lua(), -1)) {
		std::cout << "[ERROR] item has no action " << p_id << std::endl;
		return item;
	}
	std::string action = lua_tostring(Lua(), -1);

	// Clean stack
	lua_pop(Lua(), -1);

	if      (action == "Attack") item.m_action = eACTION::ATTACK;
	else if (action == "Heal")   item.m_action = eACTION::HEAL;
	else if (action == "Use")    item.m_action = eACTION::USE;

	// On success return item
	item.m_id = p_id;
	return item;
}

auto cItem::getID() const -> const std::string& {
	return m_id;
}

auto cItem::getName() const -> const std::string& {
	return m_name;
}

auto cItem::getRange() const -> std::pair<int, int> {
	return std::pair<int, int>{m_minRange, m_maxRange};
}

auto cItem::getType() const -> eITEM {
	return m_type;
}

auto cItem::getAction() const -> eACTION {
	return m_action;
}
