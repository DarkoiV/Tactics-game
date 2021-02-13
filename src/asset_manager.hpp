#pragma once

#include "globals.hpp"
#include <map>

class cAssetManager{
	protected:
		//Singleton constructor/destructor
		cAssetManager();
		~cAssetManager();

		//Map of pointers to assets
		std::map<std::string, SDL_Texture*> m_spriteMap;
		

	public:
		//Get instance of asset manager
		static cAssetManager& getInstance(){
			static cAssetManager instance;
			return instance;
		}

		//Get assets
		SDL_Texture* getSprite(std::string p_sAssetName);
};
