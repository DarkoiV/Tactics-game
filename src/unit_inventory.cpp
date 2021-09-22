#include "unit_inventory.hpp"

auto cUnitInventory::getFirstItem() -> cItem* {
	if(m_items.size() == 0) return nullptr;	
	return &m_items[0];
}

bool cUnitInventory::addNewItem(cItem p_item) {
	if(m_items.size() >= 5) return false;
	m_items.push_back(std::move(p_item));
	return true;
}

void cUnitInventory::makeFirst(int p_pos) {
	if(m_items.size() > p_pos or p_pos <= 0) return;
	std::swap(m_items[0], m_items[p_pos]);
}
