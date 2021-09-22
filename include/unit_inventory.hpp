#pragma once

#include "item.hpp"
#include <vector>

class cUnit;

class cUnitInventory{
	private:
		// Parent unit
		cUnit &unit;
		std::vector<cItem> m_items;

	public:
		// Constructor
		cUnitInventory(cUnit &u):
			unit(u){};

		// Get first item in inventory, or nullptr if none
		auto getFirstItem() -> cItem*;

		// Get vector with items
		auto getItems() -> const std::vector<cItem>&;

		// Adds item to inventory
		bool addNewItem(cItem p_item);

		// Moves item at pos to first place
		void makeFirst(int p_pos);
};
