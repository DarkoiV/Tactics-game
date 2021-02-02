#pragma once

#include "globals.hpp"
#include <string>
#include <vector>
#include "cursor.hpp"

#define TILESET_WIDTH 6						//How many cells in tileset per line

class cMap{
	protected:
		vec2D m_vSize;					//Size in Tiles
		std::vector<sTile> m_tilesVector;		//Vector of tiles structure
		SDL_Texture* m_pTilesetSprite = NULL;		//Tileset sprite
		
	public:
		//Constructor/destructor
		cMap(vec2D p_vSize);				//Create map of size vSize //used for editor
		cMap(std::string p_sMapName);			//Load map based on its name
		~cMap();

		//Methods
		void printTilesTypes();				//Print tiles types to console

		//Edit tiles
		void tileTypeIncrease(vec2D p_vTilePos);
		void tileTypeDecrease(vec2D p_vTilePos);
		int tileTypeCopy(vec2D p_vTilePos);
		void tileTypepaste(vec2D p_vTilePos, int p_nType);

		//Get/set
		const std::vector<sTile>& refMap();		//Get map reference
		vec2D getMapSize();				//Get map size

		//Update and draw
		void update(eBUTTON p_INPUT);			//Process input and update
		void draw(vec2D p_vCameraOffset);		//Draw map

};
