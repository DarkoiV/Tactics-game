#pragma once

#include "ui_action_menu.hpp"
#include "ui_quick_stats.hpp"

class cUI {
	private:
		cActionMenu actionMenu;
		cQuickStats quickStats;

	private:
		// Constructor
		cUI();

		// Access
		auto aMenu()  -> cActionMenu&;
		auto qStats() -> cQuickStats&;
};
