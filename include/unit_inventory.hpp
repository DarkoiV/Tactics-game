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

		auto getFirstItem() -> cItem*;
};
