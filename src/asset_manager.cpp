#include "asset_manager.hpp"

//Constructor, on creation load all assets 
cAssetManager::cAssetManager(){
	//Map sprites
	m_spriteMap["plainsTileset"] = loadSprite("graphics/plainsTileset.png");
	m_spriteMap["cursor"] = loadSprite("graphics/cursor.png");

	//Unit sprites
	m_spriteMap["infantry"] = loadSprite("graphics/infantry.png");
	m_spriteMap["rangeTile"] = loadSprite("graphics/range.png");

	//Text sprites
	m_spriteMap["consoleText"] = loadSprite("graphics/consoleText.png");
}

//Destructor, frees all assets
cAssetManager::~cAssetManager(){
	for(auto& [key, value] : m_spriteMap){
		SDL_DestroyTexture(value);
	}
}

//Get sprite by name
SDL_Texture* cAssetManager::getSprite(std::string p_sAssetName){
	if(m_spriteMap.count(p_sAssetName) != 0)
		return m_spriteMap[p_sAssetName];
	else {
		std::cout << "[ERROR] Non existent asset: " << p_sAssetName << std::endl;
		return nullptr;
	}
	
}
