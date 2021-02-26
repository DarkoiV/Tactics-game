#pragma once

#include "globals.hpp"
#include "asset_manager.hpp"

//9 tile box 
class cBox{
	protected:
		vec2D m_vOriginPoint;				//Top right corner of box
		vec2D m_vTileSize;				//Size of box tile in pixels
		vec2D m_vNoOfTiles;				//Size of box in box tiles

		bool m_bVisible;

		SDL_Texture* m_pBoxSprite;
		SDL_Texture* m_pBoxBackgroundSprite;
	public:
		//Constrcutror/destructor
		cBox();

		//Methods
		void setSize(vec2D p_vNoOfTiles);		//Set size of box in tiles
		void setCapacity(vec2D p_vInnerSize);		//Set inner size of box in minimum pixels
	
		vec2D getInnerOrgin();				//Return position of first inner tile
		int getInnerLineLenght();			//Return inner line width;

		void setPosition(vec2D p_vPosOfOriginPoint);	//Set orgin point of box
		void centerBox();				//Set position of box as centered

		void draw();
};