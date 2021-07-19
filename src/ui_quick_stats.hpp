#pragma once

#include "unit.hpp"
#include "globals.hpp"
#include "ui_text.hpp"

// Quick stats HUD
class cQuickStats {
	protected:
		// Text showing stats
		cText m_HP
			= cText({10, SCREEN_HEIGHT - 35}, eTEXT_COLOR::YELLOW);
		cText m_MP
			= cText({10, SCREEN_HEIGHT - 20}, eTEXT_COLOR::RED);

		// Is HUD visible?
		bool m_visible = false;

	public:
		// Take unit to display its stats, or nullptr to display nothing
		void operator[](cUnit* p_unit);

		// Draw quick stats to screen
		void draw();
};
