#include "board.hpp"
#include "asset_manager.hpp"

// Constructor
cBoard::cBoard(){
	// Load sprite
	auto &assetAccess = cAssetManager::getInstance();
	m_sprite = assetAccess.getSprite("Board", "plains_tileset");
}

// Load map from file
bool cBoard::load(std::string p_boardName){
	if(p_boardName == "TEST"){
		std::cout << "[INFO] Testing board" << std::endl;
	}

	// Returns true when loading succeeded 
	return true;
}

void cBoard::draw(vec2D p_cameraOffset){

}
