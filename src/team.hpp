#pragma once

#include "struct_vec2D.hpp"
#include "unit.hpp"
#include <vector>
#include <memory>
#include <string>

class cTeam{
	private:
		// Units selected for battle in this team
		std::vector<std::shared_ptr<cUnit>> m_units;

		// Curently selected unit
		cUnit* m_selectedUnit = nullptr;
	public:
		// Add new unit to team by name
		void addNewUnit(std::string p_name);

		// Select unit, returns true if unit selected
		bool selectUnit(vec2D p_cursorPos);
		void deselectUnit();

		// Draw
		void drawUnits(vec2D p_cameraOffset, int p_animationFrame);
		void drawMoveRange(vec2D p_cameraOffset, int p_animationFrame);
};
