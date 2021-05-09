#include "cursor.hpp"
#include "asset_manager.hpp"
#include "globals.hpp"

// Initialize cursor on board
void cCursor::init(vec2D p_boardSize){
	// Set board size
	m_boardSize = p_boardSize;

	// Load sprite
	auto &assetAccess = cAssetManager::getInstance();
	m_sprite = assetAccess.getSprite("Cursor", "cursor");
}

// Move cursor up
void cCursor::moveUp(){
	if(m_position.y > 0)
		m_position.y--;
	else
		std::cout << "[INFO] Cursor at board limit" << std::endl;
}

// Move cursor down
void cCursor::moveDown(){
	if(m_position.y < m_boardSize.y)
		m_position.y++;
	else
		std::cout << "[INFO] Cursor at board limit" << std::endl;
}

// Move cursor left
void cCursor::moveLeft(){
	if(m_position.x > 0)
		m_position.x--;
	else
		std::cout << "[INFO] Cursor at board limit" << std::endl;
}

// Move cursor right
void cCursor::moveRight(){
	if(m_position.x < m_boardSize.x)
		m_position.x++;
	else
		std::cout << "[INFO] Cursor at board limit" << std::endl;
}

// Get cursor position
auto cCursor::position() -> vec2D{
	return m_position;
}

// Draw cursor
void cCursor::draw(vec2D p_cameraOffset, int p_animationFrame){

	SDL_Rect srcRect{ 0
			, 0
			, 30
			, 30
			};

	SDL_Rect dstRect{ (m_position.x * TILE_SIZE) + p_cameraOffset.x - 3
		        , (m_position.y * TILE_SIZE) + p_cameraOffset.y - 3
			, 30
			, 30
			};

	SDL_RenderCopy(g_renderer, m_sprite, &srcRect, &dstRect);
}
