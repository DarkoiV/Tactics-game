#include "board.hpp"
#include "asset_manager.hpp"

// Constructor
cBoard::cBoard(){
	// Load sprite
	auto &assetAccess = cAssetManager::getInstance();
	m_sprite = assetAccess.getSprite("Board", "plains_tileset");
}

// Load board from file
bool cBoard::load(std::string p_boardName){

	// Create testing board
	if(p_boardName == "TEST"){
		std::cout << "[INFO] Testing board" << std::endl;
		m_size = {25, 20};

		// Create map data
		m_tiles.resize(m_size.x * m_size.y);
		for(int y = 0; y < m_size.y; y++){
			for(int x = 0; x < m_size.x; x++){
				const int line = m_size.x * y;
				m_tiles[line + x] = (line + x) % 2;
			}
		}

		// Create river
		m_tiles[3]                = 7;
		m_tiles[m_size.x + 3]     = 7;
		m_tiles[2 * m_size.x + 3] = 7;
		m_tiles[3 * m_size.x + 3] = 7;
		m_tiles[4 * m_size.x + 3] = 8;
		m_tiles[4 * m_size.x + 2] = 6;
		m_tiles[4 * m_size.x + 1] = 6;
		m_tiles[4 * m_size.x + 0] = 6;
	}

	// Returns true when loading succeeded 
	return true;
}

// Draw board on screen
void cBoard::draw(vec2D p_cameraOffset){
	// Initialize drawing rectangles
	SDL_Rect src_rect{0, 0, TILE_SIZE, TILE_SIZE};
	SDL_Rect dst_rect{0, 0, TILE_SIZE, TILE_SIZE};

	// Draw
	for(int y = 0; y < m_size.y; y++){
		dst_rect.y = y * TILE_SIZE + p_cameraOffset.y;
		for(int x = 0; x < m_size.x; x++){
			dst_rect.x = x * TILE_SIZE + p_cameraOffset.x;

			const int line = m_size.x * y;
			src_rect.x = (m_tiles[line + x] % SPRITE_COLUMNS) * TILE_SIZE;
			src_rect.y = (m_tiles[line + x] / SPRITE_COLUMNS) * TILE_SIZE;

			SDL_RenderCopy(g_renderer, m_sprite, &src_rect, &dst_rect);
		}
	}

}

// Get board size
auto cBoard::getSize() -> vec2D{
	return m_size;
}
