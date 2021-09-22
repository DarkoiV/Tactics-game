#pragma once

#include "unit.hpp"
#include "battle_lua.hpp"
#include "enums.hpp"
#include "ui_box.hpp"
#include "ui_text.hpp"

class cActionMenu {
	private:
		// Page of action menu
		enum class ePAGE {
			GENERAL,
			ITEMS,
			ITEM_OPTIONS
		} m_currentPage;

	private:
		// Reference to lua state
		cBattleLua &Lua;

		// Pointer to unit for whom aMenu is drawn, or nullptr for hiden
		cUnit* unit;
	
		// Background box, and texts displaying subMenu and options
		cBox  m_box;
		cText m_subMenuTitle;

		// Structure holding selection options
		struct textOption {
			cText text;
			enum class eOPTION {
				ATTACK,				// Attack with first possible item(makes it 1st)
				HEAL,				// Heal with first possible item(makes it 1st)
				WAIT,				// Wait
				GO_INVENTORY,			// Go to inventory page
				GO_ITEM,			// Go to item options page
				MAKE_FIRST,			// Make item 1st
				MAKE_FIRST_ATTACK,		// Make item 1st, attack with it
				MAKE_FIRST_HEAL,		// Make item 1st, heals with it
				MAKE_FIRST_USE,			// Make item 1st, uses it
				DISCARD				// Discard item
			} option;
		};
		std::vector<textOption> m_textOptions;
	
		// Adds text option to m_textOptions vector
		void addTextOption(const std::string& p_string, textOption::eOPTION p_option);

		// Variables
		bool   m_subMenuVisible	= false;			// Is subMenuTitle visible?
		bool   m_visible 	= false;			// Is menu visible?
		bool   m_isSelected	= false;			// Is selected?
		int    m_highlighted	= 0;				// Which option is highlighted

		eACTION m_selectedAction;
		
		// General page
		void constructGeneral();

		// Inventory page
		void constructInventory();

		// Item option page
		void constructItemOptions(int p_itemNo);

		// Autoresize action menu
		void autoresize();

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

		// Draw action menu
		void draw();
};
