#pragma once

#include "globals.hpp"
#include <vector>
#include <stack>
#include <map>

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

		enum class eUNIT_STATE{				//State of unit
			IDLE,
			WALKING_NORTH,
			WALKING_SOUTH,
			WALKING_EAST,
			WALKING_WEST
		} m_unitState;

		std::map<int, int> m_rangeMap;			//Map of tiles in range, and distance to them
		std::vector<vec2D> m_rangeVector;		//Vector of tiles in range

		//Graphics
		bool m_bUsesGlobalSprite;
		SDL_Texture* m_pSprite;

	public:
		//Constructor/destructor
		cUnit();
		~cUnit();

		//Methods
		void setPosition(vec2D p_vNewPos);		//Set position on map
		void movPosition(vec2D p_vChange);		//Move position by value of vector(for animation)
		void finalizeMovement();			//Reset animation offset, and set position

		//Calculate movement range
		void calculateRange(const std::vector<sTile>& p_map, vec2D p_vMapSize);

		//Update/Draw
		void update();
		void draw(int p_nAnimationFrame, vec2D p_vCameraOffset);
		void drawRange(int p_nAnimationFrame, vec2D p_vCameraOffset);

};
