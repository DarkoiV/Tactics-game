#pragma once

#include "struct_vec2D.hpp"
#include <SDL2/SDL.h>

class cBox {
	protected:
		// Boxes are 3x3
		constexpr static int TILES_IN_LINE = 3;

		// Position and size
		vec2D m_originPoint;			// Top left point of box
		vec2D m_size;				// Size of box
		vec2D m_boxTileEdge;			// Lenght of tile edges
		int   m_margin;				// Additional lenght from border to inner capacity

		// Sprites
		SDL_Texture* m_borderSprite;
		SDL_Texture* m_backgroundSprite;

	public:
		// Constructor
		cBox();

		// Methods
		void setCapacity(vec2D p_size, int p_margin);		// Set inner capacity of box

		void setOrigin(vec2D p_orginPoint); 			// Set origin points of box (+ from top-left, - from bottom-right)
		auto getInnerOrigin() -> vec2D;				// Get origin point of inner area

		// Draw a BOX ;)
		void draw();
};
