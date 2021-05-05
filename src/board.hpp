#pragma once

#include "globals.hpp"
#include "struct_vec2D.hpp"
#include <vector>
#include <set>

class cBoard{
	private:
		// Variables
		vec2D m_size;

		// Containers storing board state
		std::vector<int> m_tiles;
		std::set<int> m_occupiedByUnit;
		std::set<int> m_occupiedByEnemy;

		// Sprite pointer
		SDL_Texture* m_sprite;

	public:
		// Constructor
		cBoard();

		// Methods
		bool load(std::string p_boardName);
		void draw(vec2D p_cameraOffset);

};
