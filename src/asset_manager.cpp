#include "asset_manager.hpp"

#include "globals.hpp"
#include <SDL2/SDL_image.h>
#include <iostream>

// Constructor, on creation load all assets 
cAssetManager::cAssetManager(){
	std::cout << "[INFO] Loading sprites " << std::endl;
	
	// Map sprites
	loadSprite("plains_tileset");
	loadSprite("cursor")        ; 

	// Unit sprites
	loadSprite("unit_infantry");
	loadSprite("enemy_infantry");
	loadSprite("move_range");
	loadSprite("attack_range");

	// Set transparency for range sprites
	SDL_SetTextureAlphaMod(m_spriteMap["move_range"], 125);
	SDL_SetTextureAlphaMod(m_spriteMap["attack_range"], 125);

	// Text sprites
	loadSprite("text_console");
	loadSprite("text_red");
	loadSprite("text_yellow");

	// Box sprite
	loadSprite("box_border");
	loadSprite("box_background");

	// Set transparency for box box_background
	SDL_SetTextureAlphaMod(m_spriteMap["box_background"], 145);
}

// Destructor, frees all sprites
cAssetManager::~cAssetManager(){
	std::cout << "[INFO] Deleting sprites from memory " << std::endl;
	for(auto& [key, sprite] : m_spriteMap){
		SDL_DestroyTexture(sprite);
	}
}

// Load sprite to map
void cAssetManager::loadSprite(std::string p_spriteName){
	// Create absolute path to sprite
	std::cout << "[INFO] Loading sprite: " << p_spriteName << std::endl;
	std::string path = g_basePath + "data/sprites/" + p_spriteName + ".png";
	std::cout << "[INFO] Loading sprite from file: " << path << std::endl;

	// Load temporary surface
	SDL_Surface* tmpSurface = IMG_Load(path.c_str());
	if(tmpSurface == nullptr){
		std::cout << "[ERROR] Could not load: " << p_spriteName << ", " << IMG_GetError() << std::endl;
		return;
	}

	// Create map entry
	m_spriteMap[p_spriteName] = SDL_CreateTextureFromSurface(g_renderer, tmpSurface);
	if(m_spriteMap[p_spriteName] == nullptr){
		std::cout << "[ERROR] Could not create sprite texture: " << p_spriteName << ", " << SDL_GetError() << std::endl;

		// Free resources
		SDL_FreeSurface(tmpSurface);
		m_spriteMap.erase(p_spriteName);
		return;
	}

	// If all went ok
	std::cout << "[OK] Sprite: " << p_spriteName << " loaded correctly" << std::endl;
	SDL_FreeSurface(tmpSurface);
}

// Get sprite by name
SDL_Texture* cAssetManager::getSprite(std::string p_requesterName, std::string p_spriteName){
	std::cout << "[INFO] " << p_requesterName << " wants pointer to asset: " << p_spriteName << std::endl;
	if(m_spriteMap.count(p_spriteName) != 0){
		std::cout << "[OK] Acess to asset granted " << std::endl;
		return m_spriteMap[p_spriteName];
	}
	else {
		std::cout << "[ERROR] Non existent asset: " << p_spriteName << std::endl;
		return nullptr;
	}
	
}