#include "ui_action_menu.hpp"

void cActionMenu::moveUp() {
	if(m_highlighted == 0)
		std::cout << "[INFO] Selection at top" << std::endl;
	else {
		m_textOptions[m_highlighted].changeTextColor(eTEXT_COLOR::YELLOW);
		m_highlighted--;
		m_textOptions[m_highlighted].changeTextColor(eTEXT_COLOR::RED);
	}
}

void cActionMenu::moveDown() {
	if(m_highlighted == (int)m_textOptions.size() - 1)
		std::cout << "[INFO] Selection at bottom" << std::endl;
	else {
		m_textOptions[m_highlighted].changeTextColor(eTEXT_COLOR::YELLOW);
		m_highlighted++;
		m_textOptions[m_highlighted].changeTextColor(eTEXT_COLOR::RED);
	}
}

void cActionMenu::select() {

}

void cActionMenu::cancel() {

}

void cActionMenu::operator[](cUnit* p_unit) {
	// Hide for nullptr
	if(p_unit == nullptr){
		m_visible = false;
		return;
	}	
	else m_visible = true;

	// Check if menu was constructed for unit, if so return
	if(p_unit == unit) return;

	// If not construct general page for unit
}

bool cActionMenu::isSelected() {
	return true;
}

auto cActionMenu::getSelectedAction() -> eACTION {
	return eACTION::WAIT;
}

void cActionMenu::autoresize() {
	// Get widest text
	int widestText = 0;
	for(size_t i = 0; i < m_textOptions.size(); i++) {
		int width = m_textOptions[i].getPixelWidth();

		if(width > widestText) widestText = width;
	}
	if(m_subMenuVisible and m_subMenuTitle.getPixelWidth() > widestText)
		widestText = m_subMenuTitle.getPixelWidth();

	// Set box
	int textHeight = m_textOptions.back().getPixelHeight();
	int boxInnerHeight = (textHeight + 2) * m_textOptions.size();
	if(m_subMenuVisible) boxInnerHeight += textHeight * 2;

	m_box.setCapacity({widestText, boxInnerHeight}, 1);
	m_box.setOrigin({0, 0});

	// Set text orgins
	vec2D textOrigin = m_box.getInnerOrigin();
	if(m_subMenuVisible) textOrigin.y += textHeight * 2;
	for(size_t i = 0; i < m_textOptions.size(); i++) {
		m_textOptions[i].setOriginPoint(textOrigin);
		textOrigin.y += textHeight + 2;
	}

	// Set submenu title
	if(m_subMenuVisible) {
		vec2D subMenuOrigin = m_box.getInnerOrigin();
		subMenuOrigin.x = subMenuOrigin.x + (widestText/2 - m_subMenuTitle.getPixelWidth()/2);
		m_subMenuTitle.setOriginPoint(subMenuOrigin);
	}
}


void cActionMenu::draw() {
	if(m_visible) {
		m_box.draw();
		for(auto &text : m_textOptions){
			text.draw();
		}

		if(m_subMenuVisible) m_subMenuTitle.draw();
	}
}
