#pragma once

#include "battle_lua.hpp"
#include "ui_action_menu.hpp"
#include "ui_quick_stats.hpp"

class cUI {
	public:
		// UI elements to be accessed
		cActionMenu aMenu;
		cQuickStats qStats;

	public:
		// Constructor
		cUI(cBattleLua &L):
			aMenu(L){};
};
