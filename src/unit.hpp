#pragma once

#include "globals.hpp"

#define UNIT_SPRITE_ROWS 5
#define UNIT_SPRITE_COLUMNS 4
#define UNIT_TILE_OFFSET -4

class cUnit{
	protected:
		vec2D m_vPos;					//Position in tiles

		enum class UNIT_STATE{				//State of unit
			IDLE,
			WALKING_NORTH,
			WALKING_SOUTH,
			WALKING_EAST,
			WALKING_WEST
		} m_unitState;

		//Graphics
		bool m_bUsesGlobalSprite;
		SDL_Texture* m_pSprite;

	public:
		//Constructor/destructor
		cUnit();
		~cUnit();

		//Methods
		void setPosition(vec2D p_vNewPos);		//Set position on map

		//Update/Draw
		void update();
		void draw(int p_nAnimationFrame, vec2D p_vCameraOffset);

};
