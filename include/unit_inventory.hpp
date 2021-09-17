#pragma once

#include "item.hpp"
#include <vector>

class cUnit;

class cUnitInventory{
	private:
		// Parent unit
		cUnit &unit;


	public:
		// Constructor
		cUnitInventory(cUnit &u):
			unit(u){};

		// Methods
		bool addItem(cItem p_newItem);		// Returns false when inventory is full
		void deleteItem(int p_itemNo);		// Deletes item on position p_itemNo

		// auto getItems()     -> const std::vector<cItem>&;
		auto getFirstItem() -> const cItem*;
};
