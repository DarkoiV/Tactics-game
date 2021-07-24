#pragma once

#include "unit.hpp"
#include "globals.hpp"
#include "ui_text.hpp"
#include "ui_box.hpp"

// Quick stats HUD
class cQuickStats {
	protected:
		// Text showing stats
		cText m_HP = cText({0, 0}, eTEXT_COLOR::YELLOW);
		cText m_MP = cText({0, 0}, eTEXT_COLOR::YELLOW);

		// Box
		cBox m_box;

		// Is HUD visible?
		bool m_visible = false;

	public:
		// Constructor
		cQuickStats();

		// Take unit to display its stats, or nullptr to display nothing
		void operator[](cUnit* p_unit);

		// Draw quick stats to screen
		void draw();
};
