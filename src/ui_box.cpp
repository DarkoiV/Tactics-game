#include "ui_box.hpp"

//Constructor
cBox::cBox(){
	auto& assets = cAssetManager::getInstance();
	m_pBoxSprite = assets.getSprite("box");
	m_pBoxBackgroundSprite = assets.getSprite("boxBackground");

	//Set dimensions for box cell
	if (SDL_QueryTexture(m_pBoxSprite, NULL, NULL, &m_vTileSize.x, &m_vTileSize.y) != 0)
		std::cout << "[ERROR] Box couldn't get texture dimensions: " << SDL_GetError() << std::endl;

	m_vTileSize.x = m_vTileSize.x/3;
	m_vTileSize.y = m_vTileSize.y/3;

	m_vOriginPoint = {30, 30};
	m_vNoOfTiles = {7, 7};
}

//Set size in tiles
void cBox::setSize(vec2D p_vNoOfTiles){
	m_vNoOfTiles = p_vNoOfTiles;
}

//Get inner box size in pixels
vec2D cBox::getCapacity(){
	return {(m_vNoOfTiles.x - 2) * m_vTileSize.x, (m_vNoOfTiles.y - 2) * m_vNoOfTiles.y};
}

//Set position of box
void cBox::setPosition(vec2D p_vPos){
	m_vOriginPoint = p_vPos;
}

//Draw a box, wink wink
void cBox::draw(){
	SDL_Rect srcRect = {0, 0, m_vTileSize.x, m_vTileSize.y};
	SDL_Rect dstRect = {m_vOriginPoint.x, m_vOriginPoint.y, m_vTileSize.x, m_vTileSize.y};
	
	//Draw box
	for(int y = 0; y < m_vNoOfTiles.y; y++){
		if(y == 0) 
			srcRect.y = 0;		
		else if(y < m_vNoOfTiles.y -1)
			srcRect.y = m_vTileSize.y;
		else
			srcRect.y = m_vTileSize.y * 2;
		dstRect.y = m_vOriginPoint.y + m_vTileSize.y * y;
		//Draw x line
		for(int x = 0; x < m_vNoOfTiles.x; x++){	
			if(x == 0) 
				srcRect.x = 0;		
			else if(x < m_vNoOfTiles.x -1)
				srcRect.x = m_vTileSize.x;
			else
				srcRect.x = m_vTileSize.x * 2;
			dstRect.x = m_vOriginPoint.x + m_vTileSize.y * x;

			SDL_RenderCopy(g_renderer, m_pBoxBackgroundSprite, &srcRect, &dstRect);
			SDL_RenderCopy(g_renderer, m_pBoxSprite, &srcRect, &dstRect);
		}	
	}
}
