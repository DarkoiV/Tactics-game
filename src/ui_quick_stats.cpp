#include "ui_quick_stats.hpp"

// Get unit which stats will be displayed
void cQuickStats::operator[](cUnit *p_unit) {
	if (p_unit == nullptr) {
		m_visible = false;
		return;
	} 
	else {
		m_visible = true;
		// TODO: Get stats
		int hp = 0;
		int mp = 0;
		m_HP.update("HP: " + std::to_string(hp));
		m_MP.update("MP: " + std::to_string(mp));
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
