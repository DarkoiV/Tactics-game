#pragma once

#include "globals.hpp"
#include "asset_manager.hpp"
#include <string>
#include <vector>
#include "cursor.hpp"

#define TILESET_WIDTH 6						//How many cells in tileset per line

class cMap{
	protected:
		vec2D m_vSize;					//Size in Tiles
		std::vector<sTile> m_tilesVector;		//Vector of tiles structure
		SDL_Texture* m_pTilesetSprite = nullptr;	//Tileset sprite

		std::vector<vec2D> m_enemySpawnPoints;		//Places where enemies will be spawned
		
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

		void createSpawnPoint(vec2D p_vPos);
		void deleteSpawnPoint(vec2D p_vPos);

		//Get/set
		const std::vector<sTile>& refMap();		//Get map reference
		vec2D getMapSize();				//Get map size
		void setTilesMovCost();				//Set tiles movement cost

		//Update and draw
		void update(eBUTTON p_INPUT);			//Process input and update
		void draw(vec2D p_vCameraOffset);		//Draw map

		//Load/Save map
		bool loadMap(std::string p_sMapName);
		void saveMap(std::string p_sMapName);

};

struct sMapFileHeader{
	//Map dimensions
	u_int8_t size_x;					//Map width in tiles  (30 - 99)
	u_int8_t size_y;					//Map height in tiles (30 - 99)
	u_int32_t tilesCheckSum;				//Sum of all map IDs 

	//Spawners
	u_int8_t noOfEnemySpawnPoints;				//How many places where enemies will be spawned

};
