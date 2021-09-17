#pragma once

#include "enums.hpp"
#include "battle_lua.hpp"

#include <iostream>
#include <tuple>

class cItem {
	private:
		// Indentification
		std::string m_id;

		// Range of items action
		int m_minRange;
		int m_maxRange;

		eACTION m_action;
		eITEM   m_type;

		cItem();

	public:
		// Create new item by ID, requires lua state with items data
		static auto newItem(std::string& p_id, cBattleLua& Lua) -> cItem;

		// Get ID of item
		auto getID() const -> const std::string&;

		// Get range of item
		auto getRange() const -> std::pair<int, int>;
};
