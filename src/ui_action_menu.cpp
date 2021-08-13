#include "ui_action_menu.hpp"
#include "lua.hpp"

// Constructor
cActionMenu::cActionMenu(cBattleLua &L): Lua(L){

}

// Construct menu for unit
void cActionMenu::construct(cUnit* p_unit){
	// Options
	bool oAttack 	= false;
	bool oHeal 	= false;
	bool oItems	= false;

	// Check unit inventory
	auto const inventoryItems = p_unit->inventory().getItems();
	bool items = (inventoryItems.size() > 0) ? true : false;
	if (items) oItems = true;

	// Loop through items, and add options to action menu
	for(const auto &item : inventoryItems){
		// Check for item data in lua
		lua_getglobal(Lua(), item.name.c_str());
		if (not lua_istable(Lua(), -1)){
			std::cout << "[ERROR] " << item.name << " is not item table, ignoring" << std::endl;
			continue;
		}

		// Get name of this item
		lua_getfield(Lua(), -1, "name");
		if (not lua_isstring(Lua(), -1) ){
			std::cout << "[ERROR] " << item.name << " name is not string" << std::endl;
			continue;
		}
		std::cout << "[INFO] Item in inventory: " << lua_tostring(Lua(), -1) << std::endl;
		lua_pop(Lua(), 1);			// Pop name


		// Get possible actions by this item
		lua_getfield(Lua(), -1, "actions");
		if (not lua_istable(Lua(), -1)){
			std::cout << "[ERROR] actions in " << item.name << " is not table." << std::endl;
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
	m_textOptions.clear();

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

	// Get widest text
	int widestText = 0;
	for(size_t i = 0; i < m_textOptions.size(); i++) {
		int width = m_textOptions[i].getPixelWidth();

		if(width > widestText) widestText = width;
	}

	// Set box
	int textHeight = m_textOptions.back().getPixelHeight();
	int boxInnerHeight = (textHeight + 2) * m_textOptions.size();
	m_box.setCapacity({widestText, boxInnerHeight}, 1);
	m_box.setOrigin({0, 0});

	// Set text orgins
	vec2D textOrigin = m_box.getInnerOrigin();
	for(size_t i = 0; i < m_textOptions.size(); i++) {
		m_textOptions[i].setOriginPoint(textOrigin);
		textOrigin.y += textHeight + 2;
	}

	// Set unit for which menu was drawn
	unit = p_unit;

	// Set first field as selected
	m_textOptions[0].changeTextColor(eTEXT_COLOR::RED);
	m_selected = 0;

	// Pop everything from lua stack
	lua_pop(Lua(), -1);
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

// Move selection up
void cActionMenu::moveUp() {
	if(m_selected == 0)
		std::cout << "[INFO] Selection at top" << std::endl;
	else {
		m_textOptions[m_selected].changeTextColor(eTEXT_COLOR::YELLOW);
		m_selected--;
		m_textOptions[m_selected].changeTextColor(eTEXT_COLOR::RED);
	}
}

// Move selection down
void cActionMenu::moveDown() {
	if(m_selected == (int)m_textOptions.size() - 1)
		std::cout << "[INFO] Selection at bottom" << std::endl;
	else {
		m_textOptions[m_selected].changeTextColor(eTEXT_COLOR::YELLOW);
		m_selected++;
		m_textOptions[m_selected].changeTextColor(eTEXT_COLOR::RED);
	}
}

// Get selected action
auto cActionMenu::getSelectedAction() -> const actionData {
	// Reset stored unti
	unit = nullptr;	
	return actionData{
		m_textOptions[m_selected]()
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
	}
}
