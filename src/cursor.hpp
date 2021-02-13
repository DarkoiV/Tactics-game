#pragma once

#include "globals.hpp"
#include "asset_manager.hpp"

#define CURSOR_SIZE 30 							//Size of cursor sprite
#define CURSOR_BORDER 3							//How much cursor goes outside tile

class cCursor{
	protected:
		vec2D m_vMapBoundary;					//Keep how far can cursor move, in Tiles
		vec2D m_vPos;						//Cursor position, in Tiles

		SDL_Texture* m_pSprite = nullptr;			//Cursor sprite
	public:
		//Constructore/destructor
		cCursor();
		~cCursor();

		//Methods
		void loadMapSize(vec2D p_vMapSize);
		void draw(int p_nAnimationFrame, vec2D p_vCameraOffset);

		//Positioning
		void setPosition(vec2D p_vPos);
		vec2D getPosition();
		int highlightedTile();
		void movUp();
		void movDown();
		void movRight();
		void moveLeft();	
};
