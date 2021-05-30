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
	std::cout << "[INFO] Loading map " << std::endl;

	// Create testing board
	if(p_boardName == "TEST"){
		std::cout << "[INFO] Testing board" << std::endl;
		m_size = {25, 20};

		// Test map in string
		std::string mapString = 
			"0101010101070101030101010"
			"1010101010171010223210101"
			"0101210101070101130101010"
			"1023323010571510101010101"
			"0102010101274451010101010"
			"1010101010375010101010101"
			"0101010101070101010101010"
			"1010101010171010101010101"
			"0101010101070101010101010"
			"1010101010196<=>66:010101"
			"0101010101010101017101010"
			"1010101010101010107010101"
			"0101010101010101017101010"
			"101010101010101010?010101"
			"010101010101010101@101010"
			"101010101010101010A010101"
			"0101010101010101017101010"
			"1010101010101010107010101"
			"0101010101010101017101010"
			"1010101010101010107010101"
			;


		// Create map data, and print it
		m_tiles.resize(m_size.x * m_size.y);
		std::cout << "[INFO] Map tiles: " << std::endl;
		for(int y = 0; y < m_size.y; y++){
			for(int x = 0; x < m_size.x; x++){
				const int line = m_size.x * y;
				m_tiles[line + x] = static_cast<uint8_t>(mapString[line + x]) - 48;

				// Print tile
				std::cout << "(";
				if(m_tiles[line + x] < 10)
					std::cout << " ";

				std::cout << static_cast<int>(m_tiles[line + x]);
				std::cout << ")";
			}
			std::cout << std::endl;
		}
		std::cout << "-----------------------------------------------"<< std::endl;
	}

	// Set passable tiles, for now based on Plains tileset
	m_passableTiles.resize(m_size.x * m_size.y);
	for(size_t i = 0; i < m_passableTiles.size(); i++){
		// Grass and trees
		if(m_tiles[i] < 6){
			m_passableTiles[i] = true;
		}
		// Bridge
		else if(m_tiles[i] == 13 or m_tiles[i] == 16){
			m_passableTiles[i] = true;
		}
		// Road
		else if(m_tiles[i] > 17){
			m_passableTiles[i] = true;
		}
		// River
		else{
			m_passableTiles[i] = false;
		}
	}

	// Print passable tiles
	std::cout << std::endl;
	std::cout << "[INFO] Passable tiles on map" << std::endl;
	for(int y = 0; y < m_size.y; y++){
		for(int x = 0; x < m_size.x; x++){
			std::cout << m_passableTiles[y * m_size.x + x];
		}
		std::cout << std::endl;
	}
	std::cout << "-----------------------------------------------"<< std::endl;

	// Returns true when loading succeeded 
	std::cout << "[INFO] Map loaded successfully" << std::endl;
	return true;
}

// Draw board on screen
void cBoard::draw(vec2D p_cameraOffset){
	// Initialize drawing rectangles
	SDL_Rect srcRect{0, 0, TILE_SIZE, TILE_SIZE};
	SDL_Rect dstRect{0, 0, TILE_SIZE, TILE_SIZE};

	// Draw
	for(int y = 0; y < m_size.y; y++){
		dstRect.y = y * TILE_SIZE + p_cameraOffset.y;
		for(int x = 0; x < m_size.x; x++){
			dstRect.x = x * TILE_SIZE + p_cameraOffset.x;

			const int line = m_size.x * y;
			srcRect.x = (m_tiles[line + x] % SPRITE_COLUMNS) * TILE_SIZE;
			srcRect.y = (m_tiles[line + x] / SPRITE_COLUMNS) * TILE_SIZE;

			SDL_RenderCopy(g_renderer, m_sprite, &srcRect, &dstRect);
		}
	}

}

// Get board size
auto cBoard::getSize() -> vec2D{
	return m_size;
}

// Get vector of tiles passable by player team
auto cBoard::getPassableForUnit() -> std::vector<bool>{
	// Copy passable tiles
	std::vector<bool> resultsVector(m_passableTiles);

	// TODO: Check here if tiles are occupied by opposing team

	// Return result
	return resultsVector;
}

// Get vector of tiles passable by enemy team
auto cBoard::getPassableForEnemy() -> std::vector<bool>{
	// Copy passable tiles
	std::vector<bool> resultsVector(m_passableTiles);

	// TODO: Check here if tiles are occupied by opposing team

	// Return result
	return resultsVector;
}
