#include "ui_action_menu.hpp"

// PAGE CONSTRUCTION //////////////////////////////////////////////////////////

void cActionMenu::constructGeneral() {
	// Reset action menu
	m_subMenuVisible = false;
	m_visible = true;
	m_highlighted = 0;
	m_textOptions.clear();

	auto inventory = unit->inventory();

	// Options 
	bool oAttack = false;
	bool oHeal = false;
	bool oItems = inventory.getItems().size() > 0 ? true : false;

	// Get possible actions from items
	for(const auto item: inventory.getItems()) {
		// Check if unit can use
		if(unit->canUse((uint8_t)item.getType())) {
			// Get actions that will be displayed in action menu
			switch(item.getAction()) {
				case eACTION::ATTACK:
					oAttack = true;
					break;

				case eACTION::HEAL:
					oHeal = true;
					break;

				default:
					break;
			}
		}
	}

	// Create textOptions
	if(oAttack) {
		m_textOptions.emplace_back( textOption {
			cText({0,0}, eTEXT_COLOR::YELLOW), textOption::ATTACK
		});
		m_textOptions.back().text.update("Attack");
	}
	if(oHeal) {
		m_textOptions.emplace_back( textOption {
			cText({0,0}, eTEXT_COLOR::YELLOW), textOption::HEAL
		});
		m_textOptions.back().text.update("Heal");
	}
	if(oItems) {
		m_textOptions.emplace_back( textOption {
			cText({0,0}, eTEXT_COLOR::YELLOW), textOption::GO_INVENTORY
		});
		m_textOptions.back().text.update("Items");
	}


	m_textOptions.emplace_back( textOption {
		cText({0,0}, eTEXT_COLOR::YELLOW), textOption::WAIT
	});
	m_textOptions.back().text.update("Wait");

	// Resize
	autoresize();

	// Set first option as highlighted
	m_textOptions[0].text.changeTextColor(eTEXT_COLOR::RED);
}

// PUBLIC METHODS /////////////////////////////////////////////////////////////

void cActionMenu::moveUp() {
	if(m_highlighted == 0)
		std::cout << "[INFO] Selection at top" << std::endl;
	else {
		m_textOptions[m_highlighted].text.changeTextColor(eTEXT_COLOR::YELLOW);
		m_highlighted--;
		m_textOptions[m_highlighted].text.changeTextColor(eTEXT_COLOR::RED);
	}
}

void cActionMenu::moveDown() {
	if(m_highlighted == (int)m_textOptions.size() - 1)
		std::cout << "[INFO] Selection at bottom" << std::endl;
	else {
		m_textOptions[m_highlighted].text.changeTextColor(eTEXT_COLOR::YELLOW);
		m_highlighted++;
		m_textOptions[m_highlighted].text.changeTextColor(eTEXT_COLOR::RED);
	}
}

void cActionMenu::select() {
	switch (m_textOptions[m_highlighted].option) {
		case textOption::WAIT :
			m_isSelected = true;
			break;

		default:
			std::cout << "[WARN] Option not handled " << std::endl;

	}
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
	unit = p_unit;
	constructGeneral();
}

bool cActionMenu::isSelected() {
	return m_isSelected;
}

auto cActionMenu::getSelectedAction() -> eACTION {
	// Reset menu
	unit = nullptr;
	m_isSelected = false;

	// Return action
	return eACTION::WAIT;
}

void cActionMenu::autoresize() {
	// Get widest text
	int widestText = 0;
	for(size_t i = 0; i < m_textOptions.size(); i++) {
		int width = m_textOptions[i].text.getPixelWidth();

		if(width > widestText) widestText = width;
	}
	if(m_subMenuVisible and m_subMenuTitle.getPixelWidth() > widestText)
		widestText = m_subMenuTitle.getPixelWidth();

	// Set box
	int textHeight = m_textOptions.back().text.getPixelHeight();
	int boxInnerHeight = (textHeight + 2) * m_textOptions.size();
	if(m_subMenuVisible) boxInnerHeight += textHeight * 2;

	m_box.setCapacity({widestText, boxInnerHeight}, 1);
	m_box.setOrigin({0, 0});

	// Set text orgins
	vec2D textOrigin = m_box.getInnerOrigin();
	if(m_subMenuVisible) textOrigin.y += textHeight * 2;
	for(size_t i = 0; i < m_textOptions.size(); i++) {
		m_textOptions[i].text.setOriginPoint(textOrigin);
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
		for(auto &textOption : m_textOptions){
			textOption.text.draw();
		}

		if(m_subMenuVisible) m_subMenuTitle.draw();
	}
}
