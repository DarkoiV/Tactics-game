#pragma once

#include "unit.hpp"
#include "battle_lua.hpp"
#include "enums.hpp"
#include "ui_box.hpp"
#include "ui_text.hpp"

class cActionMenu {
	private:
		// Reference to lua state
		cBattleLua &Lua;

		// Pointer to unit for whom aMenu is drawn, or nullptr for hiden
		cUnit* unit;
	
		// Background box, and texts displaying subMenu and options
		cBox  m_box;
		cText m_subMenuTitle;
		std::vector<cText> m_textOptions;

		// Variables
		bool   m_subMenuVisible	= false;			// Is subMenuTitle visible?
		bool   m_visible 	= false;			// Is menu visible?
		int    m_highlighted	= 0;				// Which option is highlighted

	public:
		cActionMenu(cBattleLua &L):
			Lua(L),
			m_subMenuTitle({0,0}, eTEXT_COLOR::YELLOW){};

		// Move selection inside action menu
		void moveUp();
		void moveDown();

		// Select or cancel
		void select();
		void cancel();

		// Display for unit, or nullptr to hide
		void operator[](cUnit* p_unit);

		// Return whether action was selected
		bool isSelected();
		auto getSelectedAction() -> eACTION;

		// Autoresize action menu
		void autoresize();

		// Draw action menu
		void draw();
};
