#include "unit.hpp"

//Constructor
cUnit::cUnit(){
	//Create testing unit
	m_unitState = eUNIT_STATE::IDLE;
	m_bUsesGlobalSprite = false;
	m_pSprite = loadSprite("graphics/infantry.png");
}

//Destructor
cUnit::~cUnit(){
	//If not using global sprite, free it
	if(not m_bUsesGlobalSprite){
		SDL_DestroyTexture(m_pSprite);
	}
}

//Set position on map
void cUnit::setPosition(vec2D p_vNewPos){
	m_vPos = p_vNewPos;
}

//Move position by value of vector (inPixels)
void cUnit::movPosition(vec2D p_vChange){
	m_vAnimationOffset.x += p_vChange.x;
	m_vAnimationOffset.y += p_vChange.y;
}

//Finalize movement, reset offset from animation and confirm new position
void cUnit::finalizeMovement(){
	m_vPos.x += m_vAnimationOffset.x / TILE_SIZE;
	m_vPos.y += m_vAnimationOffset.y / TILE_SIZE;
	m_vAnimationOffset = {0, 0};
}

//Update unit
void cUnit::update(){
}

//Draw to screen
void cUnit::draw(int p_nAnimationFrame, vec2D p_vCameraOffset){
	SDL_Rect srcRect;
	SDL_Rect dstRect;

	switch(m_unitState){
		case eUNIT_STATE::IDLE:
			srcRect.y = 0;
			break;
		case eUNIT_STATE::WALKING_NORTH:
			srcRect.y = TILE_SIZE;
			break;
		case eUNIT_STATE::WALKING_SOUTH:
			srcRect.y = 2 * TILE_SIZE;
			break;
		case eUNIT_STATE::WALKING_EAST:
			srcRect.y = 3 * TILE_SIZE;
			break;
		case eUNIT_STATE::WALKING_WEST:
			srcRect.y = 4 * TILE_SIZE;
			break;
	}
	//Animation frame
	srcRect.x = (p_nAnimationFrame / 15) * TILE_SIZE;

	//Set destination
	dstRect = {m_vPos.x * TILE_SIZE + p_vCameraOffset.x + m_vAnimationOffset.x, 
		m_vPos.y * TILE_SIZE + p_vCameraOffset.y + UNIT_TILE_OFFSET + m_vAnimationOffset.y, 
		TILE_SIZE, TILE_SIZE};

	//Copy to renderer
	SDL_RenderCopy(g_renderer, m_pSprite, &srcRect, &dstRect);
}
