#include "unit.hpp"
#include "globals.hpp"
#include "asset_manager.hpp"

// Test constructor
cUnit::cUnit(){
	auto &assetAcces = cAssetManager::getInstance();
	m_sprite = assetAcces.getSprite("Test unit", "unit_infantry");
}

// Set position on board
void cUnit::setPosition(vec2D p_pos){
	m_pos = p_pos;
}

// Offset position by given vector
void cUnit::offsetPosition(vec2D p_offset){
	m_offset.x += p_offset.x;
	m_offset.y += p_offset.y;
}

// Reset offset
void cUnit::resetOffset(){
	m_offset = {0, 0};
}

// Draw unit
void cUnit::draw(vec2D p_cameraOffset, int p_animationFrame){
	// Initialize drawing rectangles
	SDL_Rect srcRect{ 0 + TILE_SIZE * (p_animationFrame / 15)
			, 0
			, TILE_SIZE
			, TILE_SIZE
			};

	SDL_Rect dstRect{ m_pos.x * TILE_SIZE + m_offset.x + p_cameraOffset.x
			, m_pos.y * TILE_SIZE + m_offset.y + p_cameraOffset.y + RENDER_OFFSET
			, TILE_SIZE
			, TILE_SIZE
			};

	SDL_RenderCopy(g_renderer, m_sprite, &srcRect, &dstRect);
}
