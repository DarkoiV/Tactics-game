#include "unit_inventory.hpp"

auto cUnitInventory::getFirstItem() -> cItem* {
	if(m_items.size() == 0) return nullptr;	
	return &m_items[0];
}

auto cUnitInventory::getItems() -> const std::vector<cItem>& {
	return m_items;
}

bool cUnitInventory::addNewItem(cItem p_item) {
	if(m_items.size() >= 5) return false;
	m_items.push_back(std::move(p_item));
	return true;
}

void cUnitInventory::makeFirst(uint p_pos) {
	if(m_items.size() < p_pos) return;
	std::swap(m_items[0], m_items[p_pos]);
}

void cUnitInventory::discardItem(uint p_pos) {
	if(m_items.size() < p_pos) return;
	std::cout << "[WARN] Something tried to discard non-existing item" << std::endl;
	m_items.erase(m_items.begin() + p_pos);
}
