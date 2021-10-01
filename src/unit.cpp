#include "unit.hpp"
#include "globals.hpp"
#include "asset_manager.hpp"

// Constructor by name
cUnit::cUnit(const std::string &p_name, eTEAM_COLOR p_color){
	// Set name
	m_name = p_name;

	// Name of asset
	std::string assetToLoad = "unit_" + p_name + "_";
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
	m_stats.MP  = 10;
	m_stats.DEF = 2;
	m_stats.STR = 2;
	m_stats.MOV = 5 ;

	// Add useable items
	m_useableItems += (uint8_t)eITEM::SWORD;
	m_useableItems += (uint8_t)eITEM::SPEAR;
	m_useableItems += (uint8_t)eITEM::BOW;
	m_useableItems += (uint8_t)eITEM::POTION;
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

// Toggle active
void cUnit::toggleActive(bool p_active){
	m_active = p_active;
}

// Get unit stats
auto cUnit::getStats() -> const sStats&{
	return m_stats;
}

// Check if unit can use item
bool cUnit::canUse(uint8_t p_itemType){
	return (m_useableItems & p_itemType) == p_itemType; 
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

	if(m_active) SDL_RenderCopy(g_renderer, m_sprite, &srcRect, &dstRect);
	else {
		SDL_SetTextureColorMod(m_sprite, 125, 125, 125);
		SDL_RenderCopy(g_renderer, m_sprite, &srcRect, &dstRect);
		SDL_SetTextureColorMod(m_sprite, 255, 255, 255);
	}
}

// Get position
auto cUnit::getPosition() -> vec2D{
	return m_pos;
}

// Get range
auto cUnit::range() -> cUnitRange&{
	return m_range;
}

// Get inventory
auto cUnit::inventory() -> cUnitInventory&{
	return m_inventory;
}
