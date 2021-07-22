#include "ui_quick_stats.hpp"

// Get unit which stats will be displayed
void cQuickStats::operator[](cUnit *p_unit) {
	if (p_unit == nullptr) {
		m_visible = false;
		return;
	} 
	else {
		// Make HUD visible
		m_visible = true;
	
		// Get unit stats
		auto stats = p_unit->getStats();

		// Send them to text
		m_HP.update("HP: " + std::to_string(stats.HP));
		m_MP.update("MP: " + std::to_string(stats.MP));
	}
}

// Draw quick stats HUD
void cQuickStats::draw() {
	// Draw stats
	if(m_visible){
		m_HP.draw();
		m_MP.draw();
	}
}
