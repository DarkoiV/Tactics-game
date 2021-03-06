#pragma once

#include "globals.hpp"
#include "struct_vec2D.hpp"
#include <vector>
#include <set>

class cTeam;

class cBoard{
	private:
		// Variables
		vec2D m_size;

		// Containers storing board state
		std::vector<uint8_t> m_tiles;
		std::vector<bool>    m_passableTiles;

		// Sprite pointer and constants
		SDL_Texture* m_sprite;
		static constexpr int SPRITE_COLUMNS = 6;


	public:
		// Constructor
		cBoard();

		// Methods
		bool load(std::string p_boardName);
		void draw(vec2D p_cameraOffset);

		// Getters
		auto getSize() -> vec2D;

		// Get vector representing tiles passable for team
		auto getPassable(cTeam& opposingTeam)  -> std::vector<bool>;
};
