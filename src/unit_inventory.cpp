#include "unit_inventory.hpp"
#include <iostream>

// Constructor
cUnitInventory::cUnitInventory(cUnit &u) : unit(u){
}

// Add new item to inventory
bool cUnitInventory::addItem(sItem p_newItem){
	// Check if inventory is full
	if(m_keptItems > 5){
		std::cout << "[INFO] Inventory is full!" << std::endl;
		return false;
	}

	// Add new item
	m_items[m_keptItems] = p_newItem;
	m_keptItems++;
	std::cout << "[INFO] Added new item: " << p_newItem.name << ", at position: " << m_keptItems << std::endl;
	return true;
}
