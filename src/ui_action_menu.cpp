#include "ui_action_menu.hpp"
#include "lua.hpp"

// Construct menu for unit
void cActionMenu::construct(cUnit* p_unit) {
	// Reset options
	m_textOptions.clear();
	m_subMenuVisible = false;

	// Options
	bool oAttack 	= false;
	bool oHeal 	= false;
	bool oItems	= false;

	// Check unit inventory
	auto const inventoryItems = p_unit->inventory().getItems();
	bool items = (inventoryItems.size() > 0) ? true : false;
	if (items) oItems = true;

	// Loop through items, and add options to action menu
	for(const auto &item : inventoryItems) {
		// Check for item data in lua
		lua_getglobal(Lua(), item.id.c_str());
		if (not lua_istable(Lua(), -1)){
			std::cout << "[ERROR] " << item.id << " is not item table, ignoring" << std::endl;
			continue;
		}

		// Get name of this item
		lua_getfield(Lua(), -1, "name");
		if (not lua_isstring(Lua(), -1) ){
			std::cout << "[ERROR] In table " << item.id << " field name is not string" << std::endl;
			continue;
		}
		std::cout << "[INFO] Item in inventory: " << lua_tostring(Lua(), -1) << std::endl;
		lua_pop(Lua(), 1);			// Pop name


		// Get possible actions by this item
		lua_getfield(Lua(), -1, "actions");
		if (not lua_istable(Lua(), -1)){
			std::cout << "[ERROR] actions in " << item.id << " is not table." << std::endl;
			continue;
		}

		// Get actions from table
		lua_pushnil(Lua());			// Starting key
		while( lua_next(Lua(), -2) != 0){

			// Check if read value is string
			if(lua_isstring(Lua(), -1)) {
				std::string action(lua_tostring(Lua(), -1));
				std::cout << "[INFO] Item has action: " << action << std::endl;

				if( action == "Attack" ) 	
					oAttack = true;
				else if( action == "Heal" ) 
					oHeal = true;
			}

			// Pop read value
			lua_pop(Lua(), 1);
		}
		lua_pop(Lua(), 1);			// Pop key
	}

	// Create menu texts
	if (oAttack) {
		m_textOptions.emplace_back( cText({0, 0}, eTEXT_COLOR::YELLOW) );
		m_textOptions.back().update("Attack");
	}
	if (oHeal) {
		m_textOptions.emplace_back( cText({0, 0}, eTEXT_COLOR::YELLOW) );
		m_textOptions.back().update("Heal");
	}
	if (oItems) {
		m_textOptions.emplace_back( cText({0, 0}, eTEXT_COLOR::YELLOW) );
		m_textOptions.back().update("Items");
	}

	m_textOptions.emplace_back( cText({0, 0}, eTEXT_COLOR::YELLOW) );
	m_textOptions.back().update("Wait");

	// Resize
	autoresize();

	// Set unit for which menu was drawn
	unit = p_unit;

	// Set first field as highlighted
	m_textOptions[0].changeTextColor(eTEXT_COLOR::RED);
	m_highlighted = 0;

	// Pop everything from lua stack
	lua_pop(Lua(), -1);

	// Set menu page
	m_menuPage = ePAGE::GENERAL;
}

// Construct inventory page
void cActionMenu::constructInventory() {
	// Reset options
	m_textOptions.clear();
	m_subMenuVisible = true;
	m_subMenuTitle.update("Items");
	
	auto inventoryItems = unit->inventory().getItems();

	// Loop through items
	for(const auto &item : inventoryItems) {
		// Check for item data in lua
		lua_getglobal(Lua(), item.id.c_str());
		if (not lua_istable(Lua(), -1)){
			std::cout << "[ERROR] " << item.id << " is not item table, ignoring" << std::endl;
			continue;
		}

		// Get name of this item
		lua_getfield(Lua(), -1, "name");
		if (not lua_isstring(Lua(), -1) ){
			std::cout << "[ERROR] In table " << item.id << " name is not string" << std::endl;
			continue;
		}

		// Add item name to inventory
		m_textOptions.emplace_back( cText({0, 0}, eTEXT_COLOR::YELLOW) );
		m_textOptions.back().update(lua_tostring(Lua(), -1));

		// Pop name
		lua_pop(Lua(), 1);
	}

	// Resize
	autoresize();

	// Set first field as highlighted
	m_textOptions[0].changeTextColor(eTEXT_COLOR::RED);
	m_highlighted = 0;

	// Pop everything from lua stack
	lua_pop(Lua(), -1);

	// Set menu page
	m_menuPage = ePAGE::INVENTORY;
}

// Construct item options page
void cActionMenu::constructItemOptions() {

}

// Autoresize
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

// Display menu for unit, or hide for nullptr
void cActionMenu::operator[](cUnit *p_unit){
	// Hide for nullptr
	if(p_unit == nullptr){
		m_visible = false;
		return;
	}	
	else m_visible = true;

	// Check if menu was constructed for unit, if so return
	if(p_unit == unit) return;

	// If not construct menu for unit
	construct(p_unit);
}

// MOVE SELECTION /////////////////////////////////////////////////////////////////////////////////

// Move selection up
void cActionMenu::moveUp() {
	if(m_highlighted == 0)
		std::cout << "[INFO] Selection at top" << std::endl;
	else {
		m_textOptions[m_highlighted].changeTextColor(eTEXT_COLOR::YELLOW);
		m_highlighted--;
		m_textOptions[m_highlighted].changeTextColor(eTEXT_COLOR::RED);
	}
}

// Move selection down
void cActionMenu::moveDown() {
	if(m_highlighted == (int)m_textOptions.size() - 1)
		std::cout << "[INFO] Selection at bottom" << std::endl;
	else {
		m_textOptions[m_highlighted].changeTextColor(eTEXT_COLOR::YELLOW);
		m_highlighted++;
		m_textOptions[m_highlighted].changeTextColor(eTEXT_COLOR::RED);
	}
}

// Select button press
void cActionMenu::select() {
	switch (m_menuPage) {
		case ePAGE::GENERAL:
			if(m_textOptions[m_highlighted]() == "Items") {
				constructInventory();
			}
			else {
				m_isSelected = true;
			}
			break;

		case ePAGE::INVENTORY:
			break;

		case ePAGE::ITEM_OPTIONS:
			break;
	}
}

// Cancel button press
void cActionMenu::cancel() {
	switch (m_menuPage) {
		case ePAGE::GENERAL:
			break;

		case ePAGE::INVENTORY:
			construct(unit);
			break;

		case ePAGE::ITEM_OPTIONS:
			break;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////

// Returns true when option was selected
bool cActionMenu::isSelected() {
	return m_isSelected;
}

// Get selected action
auto cActionMenu::getSelectedAction() -> const actionData {
	// Reset stored unit and isSelected
	unit = nullptr;
	m_isSelected = false;

	// Get selected action info
	return actionData{
		m_textOptions[m_highlighted]()
		, 1 
		, 1
	};
}

// draw
void cActionMenu::draw() {
	if(m_visible) {
		m_box.draw();
		for(auto &text : m_textOptions){
			text.draw();
		}

		if(m_subMenuVisible) m_subMenuTitle.draw();
	}
}
