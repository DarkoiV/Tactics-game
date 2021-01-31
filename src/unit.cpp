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
	dstRect = {m_vPos.x * TILE_SIZE + p_vCameraOffset.x, 
		m_vPos.y * TILE_SIZE + p_vCameraOffset.y + UNIT_TILE_OFFSET, 
		TILE_SIZE, TILE_SIZE};

	//Copy to renderer
	SDL_RenderCopy(g_renderer, m_pSprite, &srcRect, &dstRect);
}
