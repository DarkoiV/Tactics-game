#pragma once

#include "globals.hpp"
#include <string>
#include <vector>
#include "cursor.hpp"

#define TILESET_WIDTH 6						//How many cells in tileset per line

class cMap{
	protected:
		vec2D m_vSize;					//Size in Tiles
		vec2D m_vCameraOffset = {0, 0};			//Camera offset in pixels
		std::vector<sTile> m_tilesVector;		//Vector of tiles structure
		enum class eMAP_STATE{				//Map mode
			NEW_TURN,
			EDIT_MODE,
			NORMAL_MODE,
			UNIT_MODE,
			ENEMY_TURN
		} m_mapState;
		SDL_Texture* m_tilesetSprite = NULL;		//Tileset sprite
		
		cCursor m_cursor;				//Cursor object
		int m_nAnimationFrameCounter = 0;		//Counter for animations

		//Update functions for differnt modes
		void updateNewTurn();
		void updateEditMode(eBUTTON p_INPUT);
		void updateNormalMode(eBUTTON p_INPUT);
		void updateUnitMode(eBUTTON p_INPUT);
		void updateEnemyTurn();

	public:
		//Constructor/destructor
		cMap(std::string p_mapName);			//Load map based on its name
		~cMap();

		//Update and draw
		void update(eBUTTON p_INPUT);			//Process input and update
		void draw();					//Draw map
};
