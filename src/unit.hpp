#pragma once

#include "globals.hpp"
#include "asset_manager.hpp"
#include <vector>
#include <stack>
#include <map>
#include <set>

#define UNIT_SPRITE_ROWS 5
#define UNIT_SPRITE_COLUMNS 4
#define UNIT_TILE_OFFSET -4

struct sUnitAttributes{
	int HP;							//Unit current health
	int maxHP;						//Unit max hp
	int mov;						//Unit max travelable distance
};

class cUnit{
	protected:
		sUnitAttributes m_unitAttributes;				
		vec2D m_vPos;					//Position in tiles
		vec2D m_vAnimationOffset = {0,0};		//Offset for animation

		Uint8 m_unitPossibleActionFlags;		//Possible actions of this unit, as defined by flags

		enum class eUNIT_STATE{				//State of unit
			IDLE,
			WALKING_NORTH,
			WALKING_SOUTH,
			WALKING_EAST,
			WALKING_WEST
		} m_unitState;

		std::map<int, int> m_rangeMap;			//Map of tiles in range, and distance to them
		std::vector<vec2D> m_rangeVector;		//Vector of tiles in range

		bool m_bExhausted = false;			//Units get exhausted after move

		//Graphics
		SDL_Texture* m_pSprite;
		SDL_Texture* m_pRangeTile;

	public:
		//Constructor/destructor
		cUnit(std::string p_sUnitType);
		~cUnit();

		//Methods
		void setPosition(vec2D p_vNewPos);		//Set position on map
		void movPosition(vec2D p_vChange);		//Move position by value of vector(for animation)
		void finalizeMovement();			//Reset animation offset, and set position
		void resetPosition(vec2D p_vMapSize);		//Reset position to that on turn start

		bool isHere(vec2D p_vPos);			//Returns true when unit pos matches passed vector
		bool isMoveInRange(int p_nTargetTile);		//Returns true when tile is within range of a unit
		int occupiesTile(vec2D p_vMapSize);		//Returns tile which is occupied by unit

		//Exhaustion methods
		void setExhausted();
		void setNotExhausted();
		bool isNotExhausted(){return !m_bExhausted;};

		Uint8 getPossibleActions();			//Returns flags for possible actions of unit

		//Calculate movement range, and path
		void calculateRange(const std::vector<sTile>& p_mapTiles, 
				const std::set<int>& p_TilesOccupiedByOposingTeam, 
				vec2D p_vMapSize);
		std::stack<eDIRECTION> getPathToTile(int p_nTargetTile, vec2D p_vMapSize);

		//Update/Draw
		void update();
		void draw(int p_nAnimationFrame, vec2D p_vCameraOffset);
		void drawRange(int p_nAnimationFrame, vec2D p_vCameraOffset);

};
