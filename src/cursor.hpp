#pragma once

#include "struct_vec2D.hpp"

#include <SDL2/SDL.h>

// Cursor display mode
enum class eCURSOR_MODE : int {
	NORMAL,
	ENEMY,
	ALLY
};

// Cursor class
class cCursor{
	private:
		// Display mode
		eCURSOR_MODE m_mode = eCURSOR_MODE::NORMAL;

		// Position in TILES
		vec2D m_position{0, 0};

		// Size of board in TILES
		vec2D m_boardSize{0, 0};

		// Sprite used for drawing
		SDL_Texture* m_sprite = nullptr;
	public:
		// Init on board
		void init(vec2D p_boardSize);

		// Move cursor
		void moveUp();
		void moveDown();
		void moveLeft();
		void moveRight();

		// Change mode of display
		void operator[](eCURSOR_MODE p_mode);

		// Get position
		auto position() -> vec2D;

		// Draw cursor
		void draw(vec2D p_cameraOffset, int p_animationFrame);
};
