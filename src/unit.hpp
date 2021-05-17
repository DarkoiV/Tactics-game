#pragma once

#include "unit_range.hpp"
#include "struct_vec2D.hpp"
#include "struct_stats.hpp"
#include <SDL2/SDL.h>

class cUnit{
	private:
		// Position on map in tiles, offset in pixels
		vec2D m_pos{-1, -1};
		vec2D m_offset{0, 0};
		static constexpr int RENDER_OFFSET = -3;

		// Stats
		sStats m_stats;

		// Components
		cUnitRange m_range;
		friend cUnitRange;

		// Sprite
		SDL_Texture* m_sprite;
	public:
		// Constructor
		cUnit();

		// Methods for position
		void setPosition(vec2D p_pos);
		void offsetPosition(vec2D p_offset);
		void resetOffset();

		// Drawing
		void draw(vec2D p_cameraOffset, int p_animationFrame);

		// Get components
		auto range() -> cUnitRange&;
};
