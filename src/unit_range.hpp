#pragma once

#include "enums.hpp"
#include "struct_vec2D.hpp"
#include <SDL2/SDL.h>
#include <vector>
#include <map>
#include <stack>

class cUnit;
class cBoard;
class cTeam;

class cUnitRange{
	private:
		// Parent unit
		cUnit &unit;

		// Containers storing range data
		std::vector<vec2D> m_validMove;			// Valid move targets (vector for drawing) 
		std::map<int, int> m_validMoveDistance;		// Distance to valid move (distance to tile)

		std::vector<vec2D> m_validAction;		// Valid move targets (vector for drawing) 
		std::map<int, int> m_validActionDistance;	// Distance to valid move (distance to tile)

		// Sprite
		SDL_Texture* m_moveRangeSprite;	
		SDL_Texture* m_actionRangeSprite;	

	public:
		// Constructor loads sprites
		cUnitRange(cUnit &u);

		// Move range
		void calculateRange(cBoard &board, std::vector<bool> passableTiles);		// Calculates range
		void calculateActionRange(cBoard &board, int minRange, int maxRange);		// Calculates attack range

		bool inRange(cBoard &board, vec2D p_targetPos);					// Returns true if targetPos is valid move
		auto getPath(cBoard &board, vec2D p_targetPos) -> std::stack<eDIRECTION>;	// Get Stack of path directions

		// Draw
		void drawMoveRange(vec2D p_cameraOffset, int p_animationFrame);
		void drawActionRange(vec2D p_cameraOffset, int p_animationFrame);
};
