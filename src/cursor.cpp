#include "cursor.hpp"

//Constructor
cCursor::cCursor(){
	m_sprite = loadSprite("graphics/cursor.png");
}

//Destructor
cCursor::~cCursor(){
	SDL_DestroyTexture(m_sprite);
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
	dstRect = {TILE_SIZE * m_vPos.x - CURSOR_BORDER, 
		TILE_SIZE * m_vPos.y - CURSOR_BORDER, 
		CURSOR_SIZE, CURSOR_SIZE};
		
	SDL_RenderCopy(g_renderer, m_sprite, &srcRect, &dstRect);
}

//Set position
void cCursor::setPosition(vec2D p_vPos){
	m_vPos = p_vPos;
}

//Get position
vec2D cCursor::getPosition(){
	return m_vPos;
}

//Move cursor up
void cCursor::movUp(){
}

//Move cursor down
void cCursor::movDown(){
}

//Move cursor right
void cCursor::movRight(){
}

//Move cursor left
void cCursor::moveLeft(){
}
