#pragma once

#include <SDL2/SDL.h>
#include <map>

class cAssetManager{
	protected:
		// Singleton constructor/destructor
		cAssetManager();

		// Map of pointers to sprites
		std::map<std::string, SDL_Texture*> m_spriteMap;

		// Load sprite
		void loadSprite(std::string p_spriteName);
	
	public:
		// Free resources
		void freeResources();

		// Get instance of asset manager
		static cAssetManager& getInstance(){
			static cAssetManager instance;
			return instance;
		}

		// Get sprite pointer
		SDL_Texture* getSprite(const std::string& p_requesterName, const std::string& p_spriteName);
};
