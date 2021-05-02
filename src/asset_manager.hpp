#pragma once

#include <SDL2/SDL.h>
#include <map>

class cAssetManager{
	protected:
		// Singleton constructor/destructor
		cAssetManager();
		~cAssetManager();

		// Map of pointers to sprites
		std::map<std::string, SDL_Texture*> m_spriteMap;

		// Load sprite
		void loadSprite(std::string p_spriteName);
		
	public:
		// Get instance of asset manager
		static cAssetManager& getInstance(){
			static cAssetManager instance;
			return instance;
		}

		// Get sprite pointer
		SDL_Texture* getSprite(std::string p_requesterName, std::string p_spriteName);
};