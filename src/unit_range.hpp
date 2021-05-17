#pragma once

#include "struct_vec2D.hpp"
#include <SDL2/SDL.h>
#include <vector>
#include <map>

class cUnit;
class cSceneBattle;

class cUnitRange{
	private:
		// Containers storing range data
		std::vector<vec2D> m_validMove;			// Valid move targets (vector for drawing) 
		std::map<int, int> m_validMoveDistance;		// Distance to valid move (distance to tile)

		// Sprite
		SDL_Texture* m_moveRangeSprite;	

	public:
		// Constructor loads sprites
		cUnitRange();

		// Move range
		void calculateRange(						// Calculate possible moves of unit
			cUnit &unit,
			cSceneBattle &scene,
			const std::vector<bool> &passableTiles
			);
		bool canMove(cSceneBattle &scene, vec2D p_targetPos);		// Returns true if targetPos is valid move

		// Draw
		void drawMoveRange(vec2D p_cameraOffset, int p_animationFrame);
};
