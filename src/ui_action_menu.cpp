#include "ui_action_menu.hpp"

// Constructor
cActionMenu::cActionMenu(cBattleLua &L): Lua(L){

}

// TODO
void cActionMenu::operator[](cUnit *p_unit){
	// Hide for nullptr
	if(p_unit == nullptr){
		m_visible = true;
		return;
	}
	// Check if menu was constructed for unit, if so return
	if(p_unit == unit) return;

	// If not construct menu for unit
}

// draw
void cActionMenu::draw() {
	m_box.draw();
	for(auto &text : m_textOptions){
		text.draw();
	}
}
