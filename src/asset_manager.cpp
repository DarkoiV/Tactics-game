#include "asset_manager.hpp"

//Constructor, on creation load all assets 
cAssetManager::cAssetManager(){
	std::cout << "[INFO] Loading assets " << std::endl;
	//Map sprites
	m_spriteMap["plainsTileset"] = loadSprite("graphics/plainsTileset.png");
	m_spriteMap["cursor"] = loadSprite("graphics/cursor.png");

	//Unit sprites
	m_spriteMap["infantry"] = loadSprite("graphics/infantry.png");
	m_spriteMap["enemyInfantry"] = loadSprite("graphics/enemyInfantry.png");
	m_spriteMap["rangeTile"] = loadSprite("graphics/range.png");
	SDL_SetTextureAlphaMod(m_spriteMap["rangeTile"], 125);

	//Text sprites
	m_spriteMap["consoleText"] = loadSprite("graphics/consoleText.png");
	m_spriteMap["textColor1"] = loadSprite("graphics/gnshText1.png");

	//Box sprite
	m_spriteMap["box"] = loadSprite("graphics/box.png");
	m_spriteMap["boxBackground"] = loadSprite("graphics/boxBackground.png");
	SDL_SetTextureAlphaMod(m_spriteMap["boxBackground"], 145);
}

//Destructor, frees all assets
cAssetManager::~cAssetManager(){
	std::cout << "[INFO] Destroying assets " << std::endl;
	for(auto& [key, value] : m_spriteMap){
		SDL_DestroyTexture(value);
	}
}

//Get sprite by name
SDL_Texture* cAssetManager::getSprite(std::string p_sAssetName){
	std::cout << "[INFO] Objects wants pointer to asset: " << p_sAssetName << std::endl;
	if(m_spriteMap.count(p_sAssetName) != 0)
		return m_spriteMap[p_sAssetName];
	else {
		std::cout << "[ERROR] Non existent asset: " << p_sAssetName << std::endl;
		return nullptr;
	}
	
}
