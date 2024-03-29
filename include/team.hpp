#pragma once

#include "struct_vec2D.hpp"
#include "unit.hpp"
#include "battle_lua.hpp"

#include <vector>
#include <memory>
#include <string>

class cCommander;

// Team class
class cTeam{
	private:
		// ~ LUA ~
		cBattleLua &Lua;

		// Units selected for battle in this team
		std::vector<std::unique_ptr<cUnit>> m_units;

		// Curently selected unit
		cUnit* m_selectedUnit = nullptr;
		bool m_showMoveRange = false;
		bool m_showActionRange = false;

		// Color of team
		eTEAM_COLOR m_teamColor;

	public:
		// Constructor decides which color are units
		cTeam(cBattleLua &L, eTEAM_COLOR p_teamColor):
			Lua(L),
			m_teamColor(p_teamColor){};

		cTeam(cTeam&) = delete;
		cTeam(cTeam&&) = delete;

		// Spawn new unit by name
		void spawnUnit(const std::string& p_name, vec2D p_pos);

		// Check units status
		int checkDeadUnits();		// Returns how many units have died, and deletes them from vactor
		bool checkForActive();		// Returns false when no unit remains active
		bool alive();			// Returns false when no unit remains alive

		// Select unit, returns true if unit selected
		bool selectUnit(vec2D p_targetPos);
		void deselectUnit();

		// Get selected unit
		auto selected() -> cUnit&;

		// Calculate range of units
		void calculateRange(cBoard &board, cTeam &opposingTeam);

		// Get occupied tiles by team
		auto getOccupiedTiles() -> std::vector<vec2D>;

		// Return if there is any unit at target position
		bool isAnyHere(vec2D p_targetPos, cUnit** unitHere);

		// Toogle
		void toggleMoveRange(bool p_shown);
		void toggleActionRange(bool p_shown);

		// Make all units active
		void resetActiveStatus();

		// Draw
		void drawUnits(vec2D p_cameraOffset, int p_animationFrame);
		void drawRange(vec2D p_cameraOffset, int p_animationFrame);
};
