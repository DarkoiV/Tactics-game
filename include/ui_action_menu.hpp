#pragma once

#include "ui_box.hpp"
#include "ui_text.hpp"
#include "unit.hpp"
#include "battle_lua.hpp"
#include <vector>

class cActionMenu {
	public:
		// data about action
		struct actionData {
			std::string& 	actionName;
			int 		minRange;
			int 		maxRange;
		};

	private:
		// ~ LUA ~
		cBattleLua &Lua;				// Acces to Lua state

		// Background box, and texts displaying options
		cBox m_box;
		std::vector<cText> m_textOptions;

		// Contruct menu for unit
		void construct(cUnit *p_unit);

		// Variables
		bool   m_visible  = false;			// Is menu visible?
		int    m_selected = 0;				// Which option is selected
		cUnit* unit       = nullptr;			// Pointer to unit for which menu is displayed

	public:
		// Constructor
		cActionMenu(cBattleLua &L);

		// Display menu for unit, or hide for nullptr
		void operator[](cUnit* p_unit);		

		// Move selection
		void moveUp();
		void moveDown();

		auto getSelectedAction() -> const actionData;

		// Draw menu
		void draw();
};
