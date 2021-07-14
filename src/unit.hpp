#pragma once

#include "unit_range.hpp"
#include "unit_inventory.hpp"
#include "struct_vec2D.hpp"
#include "struct_stats.hpp"
#include <SDL2/SDL.h>

class cUnit{
	private:
		// Identification
		std::string m_name;

		// Position on map in tiles, offset in pixels
		vec2D m_pos{-1, -1};
		vec2D m_offset{0, 0};
		static constexpr int RENDER_OFFSET = -3;

		// Stats
		sStats m_stats;

		// Components ////////////////
		cUnitRange m_range = cUnitRange(*this);
		friend cUnitRange;
		
		cUnitInventory m_inventory = cUnitInventory(*this);
		friend cUnitInventory;

		//////////////////////////////

		// Sprite
		SDL_Texture* m_sprite;
	public:
		// Constructor
		cUnit(std::string p_name);

		// Methods for position
		void setPosition(vec2D p_pos);
		void offsetPosition(vec2D p_offset);
		void resetOffset();

		// Drawing
		void draw(vec2D p_cameraOffset, int p_animationFrame);

		// Get position
		auto getPosition() -> vec2D;

		// Access components
		auto range() -> cUnitRange&;
};
