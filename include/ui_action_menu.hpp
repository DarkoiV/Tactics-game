#pragma once

#include "ui_box.hpp"
#include "ui_text.hpp"
#include "unit.hpp"
#include "battle_lua.hpp"
#include <vector>

class cActionMenu {
	public:
		// Data about action
		struct actionData {
			std::string& 	actionName;
			int 		minRange;
			int 		maxRange;
		};

	private:
		// State of action menu
		enum class ePAGE {
			GENERAL,
			INVENTORY,
			ITEM_OPTIONS
		} m_menuPage = ePAGE::GENERAL;

		// ~ LUA ~
		cBattleLua &Lua;				// Acces to Lua state

		// Background box, and texts displaying options
		cBox  m_box;
		cText m_subMenuTitle;

		std::vector<cText> m_textOptions;

		// Contruct menu for unit
		void construct(cUnit *p_unit);

		// Construct pages of inventory
		void constructInventory();
		void constructItemOptions(int p_pos);

		// Autoresize
		void autoresize();

		// Variables
		bool   m_subMenuVisible	= false;			// Is subMenuTitle visible?
		bool   m_visible 	= false;			// Is menu visible?
		int    m_highlighted	= 0;				// Which option is highlighted
		bool   m_isSelected	= false;			// True when option was selected 
		cUnit* unit       	= nullptr;			// Pointer to unit for which menu is displayed

		// Action data
		std::string returnAction{"Wait"};
		int minRange = 1;
		int maxRange = 1;

	public:
		// Constructor
		cActionMenu(cBattleLua &L)
			: Lua(L)
			, m_subMenuTitle({0,0}, eTEXT_COLOR::YELLOW){};

		// Display menu for unit (hide for nullptr)
		void operator[](cUnit* p_unit);		

		// Move selection
		void moveUp();
		void moveDown();
		void select();
		void cancel();

		bool isSelected();
		auto getSelectedAction() -> const actionData;

		// Draw menu
		void draw();
};
