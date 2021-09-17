#pragma once

#include "enums.hpp"

#include <iostream>

class cItem {
	private:
		// Indentification
		std::string m_id;

		// Range of items action
		int minRange;
		int maxRange;

		eACTION itemAction;

		cItem();

	public:
		// Create new item by ID
		static auto newItem(std::string& p_id) -> cItem;

		auto getID() const -> const std::string&;

};
