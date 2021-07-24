#include "ui_quick_stats.hpp"

cQuickStats::cQuickStats(){
	// Dummy string
	m_HP.update("HP: XX");

	// Set box properties based on text dimensions
	int textWidth  = m_HP.getPixelWidth();
	int textHeight = m_HP.getPixelHeight();

	vec2D innerDimensions{
		textWidth,
		textHeight * 2 + V_SPACE_TEXT,
	};

	m_box.setCapacity(innerDimensions, 2);
	m_box.setOrigin({5, -5});

	// Set text orgin points based on box
	vec2D innerOrgin = m_box.getInnerOrigin();
	m_HP.setOriginPoint(innerOrgin);

	innerOrgin.y = innerOrgin.y + textHeight + V_SPACE_TEXT;		// Move MP orgin down in relation to HP
	m_MP.setOriginPoint(innerOrgin);
	
}

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
		m_box.draw();
		m_HP.draw();
		m_MP.draw();
	}
}
