#include "ui_action_menu.hpp"

void cActionMenu::addTextOption(const std::string& p_string, textOption::eOPTION p_option) {
	m_textOptions.emplace_back( textOption {
		cText({0,0}, eTEXT_COLOR::YELLOW), p_option
	});
	m_textOptions.back().text.update(p_string);
}

// PAGE CONSTRUCTION //////////////////////////////////////////////////////////

void cActionMenu::constructGeneral() {
	// Setup page
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
	for(const auto &item: inventory.getItems()) {
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
	if(oAttack) 	addTextOption("Attack", textOption::eOPTION::ATTACK);
	if(oHeal) 	addTextOption("Heal", textOption::eOPTION::HEAL);
	if(oItems) 	addTextOption("Items", textOption::eOPTION::GO_INVENTORY);

	addTextOption("Wait", textOption::eOPTION::WAIT);

	// Resize
	autoresize();

	// Set first option as highlighted
	m_textOptions[0].text.changeTextColor(eTEXT_COLOR::RED);

	// Set page as GENEREAL
	m_currentPage = ePAGE::GENERAL;
}

void cActionMenu::constructInventory() {
	// Setup page
	m_subMenuVisible = true;
	m_subMenuTitle.update("Items");
	m_visible = true;
	m_highlighted = 0;
	m_textOptions.clear();

	auto items = unit->inventory().getItems();

	for(const auto &item: items) 
		addTextOption(item.getName(), textOption::eOPTION::GO_ITEM);

	// Resize
	autoresize();

	// Set first option as highlighted
	m_textOptions[0].text.changeTextColor(eTEXT_COLOR::RED);

	// Set page as Items
	m_currentPage = ePAGE::ITEMS;
}

void cActionMenu::constructItemOptions(int p_itemNo) {
	// Setup page
	m_subMenuVisible = true;
	m_visible = true;
	m_highlighted = 0;
	m_textOptions.clear();

	// Set title as item at pos
	auto items = unit->inventory().getItems();
	m_subMenuTitle.update(items[p_itemNo].getName());

	// Add item options
	auto item = items[p_itemNo];

	// Item options for all items
	addTextOption("Make First", textOption::eOPTION::MAKE_FIRST);
	addTextOption("Discard", textOption::eOPTION::DISCARD);

	// Resize
	autoresize();

	// Set first option as highlighted
	m_textOptions[0].text.changeTextColor(eTEXT_COLOR::RED);

	// Set page as Item Options
	m_currentPage = ePAGE::ITEM_OPTIONS;
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

		// Find first item with attack, make it 1st, send action
		case textOption::eOPTION::ATTACK:
			m_isSelected = true;
			m_selectedAction = eACTION::ATTACK;
			break;

		// Send wait action
		case textOption::eOPTION::WAIT:
			m_isSelected = true;
			m_selectedAction = eACTION::WAIT;
			break;

		// Go to inventory
		case textOption::eOPTION::GO_INVENTORY:
			constructInventory();
			break;

		// Go to highlighted item
		case textOption::eOPTION::GO_ITEM:
			m_itemAcc = m_highlighted;
			constructItemOptions(m_highlighted);
			break;

		// Make item first (goes back to inventory)
		case textOption::eOPTION::MAKE_FIRST:
			unit->inventory().makeFirst(m_itemAcc);
			constructInventory();
			break;

		// Discard item
		case textOption::eOPTION::DISCARD:
			unit->inventory().discardItem(m_itemAcc);
			constructInventory();
			break;


		default:
			std::cout << "[WARN] Option not handled " << std::endl;

	}
}

void cActionMenu::cancel() {
	switch(m_currentPage) {
		// Move unit back
		case ePAGE::GENERAL:
			m_isSelected = true;
			m_selectedAction = eACTION::RETURN;
			break;

		// Go back to general page
		case ePAGE::ITEMS:
			constructGeneral();
			break;

		// Go back to items page
		case ePAGE::ITEM_OPTIONS:
			constructInventory();
			break;
	}
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
	return m_selectedAction;
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
