#include "unit_inventory.hpp"
#include <iostream>

// Constructor
cUnitInventory::cUnitInventory(cUnit &u) : unit(u){
}

// Add new item to inventory
bool cUnitInventory::addItem(sItem p_newItem){
	// Check if inventory is full
	if(m_keptItems > 5){
		std::cout << "[WARN] Inventory is full!" << std::endl;
		return false;
	}

	// Add new item
	m_items[m_keptItems] = p_newItem;
	m_keptItems++;
	std::cout << "[INFO] Added new item: " << p_newItem.name << ", at position: " << m_keptItems << std::endl;
	return true;
}

// Delete item
void cUnitInventory::deleteItem(int p_itemNo){
	// Check whether deleted item is on valid position
	if(p_itemNo > m_keptItems){
		std::cout << "[WARN] There is no item at pos " << p_itemNo << std::endl;
		return;
	}

	// Delete item
	if(p_itemNo == m_keptItems){
		m_keptItems--;
	}
	else{
		for(int i = p_itemNo; i < m_keptItems; i++){
			m_items[i] = m_items[i + 1];
		}	
		m_keptItems--;
	}
}
