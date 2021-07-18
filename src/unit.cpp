#include "unit.hpp"
#include "globals.hpp"
#include "asset_manager.hpp"

// Constructor by name
cUnit::cUnit(const std::string &p_name, eTEAM_COLOR p_color){
	// Set name
	m_name = p_name;

	// Name of asset
	std::string assetToLoad = "unit_infantry_";
	switch (p_color){
		case eTEAM_COLOR::BLUE:
			assetToLoad += "blue";
			break;
		case eTEAM_COLOR::RED:
			assetToLoad += "red";
			break;
	}

	// Set sprite
	auto &assetAcces = cAssetManager::getInstance();
	m_sprite = assetAcces.getSprite(p_name, assetToLoad);

	// Default stats
	m_stats.HP  = 10;
	m_stats.MOV = 5 ;
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

// Get position
auto cUnit::getPosition() -> vec2D{
	return m_pos;
}

// Get range
auto cUnit::range() -> cUnitRange&{
	return m_range;
}
