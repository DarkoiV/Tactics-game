#pragma once

#include "struct_item.hpp"
#include <vector>

class cUnit;

class cUnitInventory{
	private:
		// Parent unit
		cUnit &unit;

		// Items inside inventory
		std::vector<sItem> m_items;

	public:
		// Constructor
		cUnitInventory(cUnit &u):
			unit(u){};

		// Methods
		bool addItem(sItem p_newItem);		// Returns false when inventory is full
		void deleteItem(int p_itemNo);		// Deletes item on position p_itemNo

		auto getItems() -> const std::vector<sItem>&;
};
