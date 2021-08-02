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
	if(m_position.y < (m_boardSize.y - 1))
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
	if(m_position.x < (m_boardSize.x - 1))
		m_position.x++;
	else
		std::cout << "[INFO] Cursor at board limit" << std::endl;
}

// Toggle hidden
void cCursor::toggleHiden(bool p_toggle) {
	m_hidden = p_toggle;
}

// Change mode of display
void cCursor::operator[](eCURSOR_MODE p_mode) {
	m_mode = p_mode;
}

// Get cursor position
auto cCursor::position() -> vec2D{
	return m_position;
}

// Draw cursor
void cCursor::draw(vec2D p_cameraOffset, int p_animationFrame){
	if(m_hidden) return;

	// Initialize drawing rectangles
	SDL_Rect srcRect{ 30 * (p_animationFrame / 40) // 0-39 First frame 40-59 second
			, 30 * (int)m_mode  
			, 30
			, 30
			};

	SDL_Rect dstRect{ (m_position.x * TILE_SIZE) + p_cameraOffset.x - 3
		        , (m_position.y * TILE_SIZE) + p_cameraOffset.y - 3
			, 30
			, 30
			};

	// Draw cursor to renderer
	SDL_RenderCopy(g_renderer, m_sprite, &srcRect, &dstRect);
}
