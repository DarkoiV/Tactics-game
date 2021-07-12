#pragma once

#include "struct_item.hpp"

class cUnit;

class cUnitInventory{
	private:
		// Parent unit
		cUnit &unit;

		// Items inside inventory
		sItem m_items[5];
		int   m_keptItems = 0;

	public:
		// Constructor
		cUnitInventory(cUnit &u);

		// Methods
		bool addItem(sItem p_newItem);		// Returns false when inventory is full
		void deleteItem(int p_itemNo);		// Deletes item on position p_itemNo
};
