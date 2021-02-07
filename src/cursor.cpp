#include "cursor.hpp"

//Constructor
cCursor::cCursor(){
	m_pSprite = loadSprite("graphics/cursor.png");
}

//Destructor
cCursor::~cCursor(){
	//free cursor sprite
	SDL_DestroyTexture(m_pSprite);
}

//Load map size
void cCursor::loadMapSize(vec2D p_vMapSize){
	m_vMapBoundary = p_vMapSize;
}

//Draw
void cCursor::draw(int p_nAnimationFrame, vec2D p_vCameraOffset){
	SDL_Rect srcRect, dstRect;
	
	//Cursor animation
	if(p_nAnimationFrame < 40)
		srcRect = {0, 0, CURSOR_SIZE, CURSOR_SIZE};
	else
		srcRect = {CURSOR_SIZE, 0, CURSOR_SIZE, CURSOR_SIZE};

	//Cursor position
	dstRect = {TILE_SIZE * m_vPos.x - CURSOR_BORDER + p_vCameraOffset.x, 
		TILE_SIZE * m_vPos.y - CURSOR_BORDER + p_vCameraOffset.y, 
		CURSOR_SIZE, CURSOR_SIZE};
		
	SDL_RenderCopy(g_renderer, m_pSprite, &srcRect, &dstRect);
}

//Set position
void cCursor::setPosition(vec2D p_vPos){
	m_vPos = p_vPos;
}

//Get position
vec2D cCursor::getPosition(){
	return m_vPos;
}

//Return ID of highlited tile
int cCursor::highlightedTile(){
	return m_vPos.x + m_vPos.y * m_vMapBoundary.x;
}

//Move cursor up
void cCursor::movUp(){
	if(m_vPos.y > 0)
		m_vPos.y--;
	else
		std::cout << "[INFO] Cursor at map boundary" << std::endl;
}

//Move cursor down
void cCursor::movDown(){
	if(m_vPos.y < (m_vMapBoundary.y - 1))
		m_vPos.y++;
	else
		std::cout << "[INFO] Cursor at map boundary" << std::endl;
}

//Move cursor right
void cCursor::movRight(){
	if(m_vPos.x < (m_vMapBoundary.x - 1))
		m_vPos.x++;
	else
		std::cout << "[INFO] Cursor at map boundary" << std::endl;
}

//Move cursor left
void cCursor::moveLeft(){
	if(m_vPos.x > 0)
		m_vPos.x--;
	else
		std::cout << "[INFO] Cursor at map boundary" << std::endl;
}
