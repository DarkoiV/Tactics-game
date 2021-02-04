#include "unit.hpp"

//Constructor
cUnit::cUnit(){
	//Create testing unit
	m_unitState = eUNIT_STATE::IDLE;
	m_bUsesGlobalSprite = false;
	m_pSprite = loadSprite("graphics/infantry.png");
	m_unitAttributes.mov = 5;
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

//Calculate range
void cUnit::calculateRange(const std::vector<sTile> &p_map, vec2D p_vMapSize){
	//Create stack and push first position onto it
	std::stack<int>	stackOfTiles;
	stackOfTiles.push(m_vPos.x + (m_vPos.y * p_vMapSize.x));

	//Clear range map and place first tile onto it
	m_rangeMap.clear();
	m_rangeMap[m_vPos.x + (m_vPos.y * p_vMapSize.x)] = 0;

	//One line of difrence for easier calculation
	const int oneLine = p_vMapSize.x;

	//Calculate range
	while(not stackOfTiles.empty()){
		const int CURRENT_TILE = stackOfTiles.top();

		//All tiles to check
		const int NORTH_TILE = stackOfTiles.top() - oneLine;
		const int SOUTH_TILE = stackOfTiles.top() + oneLine;
		const int EAST_TILE = stackOfTiles.top() + 1;
		const int WEST_TILE = stackOfTiles.top() - 1;
		const int TILES[4] = {NORTH_TILE, SOUTH_TILE, EAST_TILE, WEST_TILE};

		//Flag
		bool bTileFound = false;

		//Check tiles
		for(int i = 0; i < 4; i++){
			//Check if tile is in range and (if was not visisted or distance is shorther than previous visit)
			if(p_map[TILES[i]].movCost + m_rangeMap[CURRENT_TILE] <= m_unitAttributes.mov
			and (!m_rangeMap.count(TILES[i]) 
			or m_rangeMap[TILES[i]] > m_rangeMap[CURRENT_TILE] + p_map[CURRENT_TILE].movCost)){
				//Add tile to map with shortest known distance
				m_rangeMap[TILES[i]] = p_map[TILES[i]].movCost + m_rangeMap[CURRENT_TILE];
				//Push tile to stack 
				stackOfTiles.push(TILES[i]);
				//Set flag that new tile found
				bTileFound = true;
				//Break out of loop
				break;
			}
		}
		//If no new reachable tile from this tile, pop the stack
		if(!bTileFound){
			stackOfTiles.pop();
		}
	}

	std::cout << std::endl;

	//create vector of range tiles
	m_rangeVector.clear();
	for(auto const& [key, value] : m_rangeMap){
		vec2D tilePos;
		tilePos.x = key % p_vMapSize.x;
		tilePos.y = key / p_vMapSize.x;
		m_rangeVector.push_back(tilePos);
	}
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

//Draw range to screen
void cUnit::drawRange(int p_nAnimationFrame, vec2D p_vCameraOffset){
	SDL_Rect srcRect = {0, 0, TILE_SIZE, TILE_SIZE};
	SDL_Rect dstRect = {0, 0, TILE_SIZE, TILE_SIZE};	

	//Set animation frame
	if(p_nAnimationFrame <= 25){
		srcRect.x = 0;
	}
	else{
		srcRect.x = TILE_SIZE + TILE_SIZE * ((p_nAnimationFrame - 25)/5);
	}

	//Draw range tiles to screen 
	for(int i = 0; i < m_rangeVector.size(); i++){
		dstRect.x = m_rangeVector[i].x * TILE_SIZE + p_vCameraOffset.x;
		dstRect.y = m_rangeVector[i].y * TILE_SIZE + p_vCameraOffset.y;
		SDL_RenderCopy(g_renderer, g_pRangeTileset, &srcRect, &dstRect);
	}
}
