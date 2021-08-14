#include "unit_inventory.hpp"
#include <iostream>

// Add new item to inventory
bool cUnitInventory::addItem(sItem p_newItem){
	// Check if inventory is full
	if(m_items.size() >= 5){
		std::cout << "[WARN] Inventory is full!" << std::endl;
		return false;
	}

	// Add new item
	m_items.push_back(p_newItem);
	std::cout << "[INFO] Added new item: " << p_newItem.id << ", at position: " << m_items.size() << std::endl;
	return true;
}

// Delete item
void cUnitInventory::deleteItem(int p_itemNo){
	// Check whether deleted item is on valid position
	if((size_t)p_itemNo > m_items.size()){
		std::cout << "[WARN] There is no item at pos " << p_itemNo << std::endl;
		return;
	}

	// Delete item
	m_items.erase(m_items.begin() + p_itemNo);
}

// Get items vector
auto cUnitInventory::getItems() -> const std::vector<sItem>& {
	return m_items;
}

// Get first item in vector
auto cUnitInventory::getFirstItem() -> const sItem* {
	if(m_items.size() == 0)
		return nullptr;

	return &m_items[0];
}
