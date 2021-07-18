#pragma once

#include "struct_vec2D.hpp"
#include "unit.hpp"

#include <vector>
#include <memory>
#include <string>

// Team class
class cTeam{
	private:
		// Units selected for battle in this team
		std::vector<std::shared_ptr<cUnit>> m_units;

		// Curently selected unit
		cUnit* m_selectedUnit = nullptr;
		bool m_showMoveRange = false;

		// Color of team
		eTEAM_COLOR m_teamColor;

	public:
		// Constructor decides which color are units
		cTeam(eTEAM_COLOR p_teamColor)
			:m_teamColor(p_teamColor){};

		// Add new unit to team by name
		void addNewUnit(std::string p_name);

		// Select unit, returns true if unit selected
		bool selectUnit(vec2D p_targetPos);
		void deselectUnit();

		// Get selected unit
		auto selected() -> cUnit&;

		// Calculate range of units
		void calculateRange(cBoard &board, const std::vector<bool> passableTiles);

		// Get occupied tiles by team
		auto getOccupiedTiles() -> std::vector<vec2D>;

		// Toogle move range
		void toggleMoveRange(bool p_shown);

		// Draw
		void drawUnits(vec2D p_cameraOffset, int p_animationFrame);
		void drawMoveRange(vec2D p_cameraOffset, int p_animationFrame);
};
