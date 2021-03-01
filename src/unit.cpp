#include "unit.hpp"

//Constructor
cUnit::cUnit(std::string p_sUnitType){
	std::cout << "[INFO] Creating unit type: " << p_sUnitType << std::endl;

	//Get asset manager instance
	cAssetManager& assets = cAssetManager::getInstance();

	//Set starting state
	m_unitState = eUNIT_STATE::IDLE;

	//Create unit
	if(p_sUnitType == "infantry"){
		m_pSprite = assets.getSprite("infantry");
		m_pRangeTile = assets.getSprite("rangeTile");
		m_unitAttributes.mov = 5;
		m_unitPossibleActionFlags = ACTION_ATTACK;
	}
	else if(p_sUnitType == "enemyInfantry"){
		m_pSprite = assets.getSprite("enemyInfantry");
		m_pRangeTile = assets.getSprite("rangeTile");
		m_unitAttributes.mov = 5;
		m_unitPossibleActionFlags = ACTION_ATTACK;
	}
	else{
		std::cout << "[ERROR] Wrong unit type" << std::endl;
	}
}

//Destructor
cUnit::~cUnit(){
	std::cout << "{INFO] Destroying unit" << std::endl;
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

//Revert position of unit to one at begining of turn
void cUnit::resetPosition(vec2D p_vMapSize){
	for(auto const& [tile, distance] : m_rangeMap){
		if(distance == 0){
			setPosition({tile % p_vMapSize.x, tile / p_vMapSize.x});
			return;
		}
	}
	std::cout << "[ERROR] No return position found! " << std::endl;
}

//Check if unit is on passed position
bool cUnit::isHere(vec2D p_vPos){
	if(m_vPos.x == p_vPos.x and m_vPos.y == p_vPos.y)
		return true;
	else
		return false;
}

//Check if tile is within range
bool cUnit::isMoveInRange(int p_nTargetTile){
	if(m_rangeMap.count(p_nTargetTile))
		return true;
	else
		return false;
}

//Return which tile is occupied by this unit
int cUnit::occupiesTile(vec2D p_vMapSize){
	return m_vPos.x + (m_vPos.y * p_vMapSize.x);
}

//Return possible actions by this unit, as Uint8 flag
Uint8 cUnit::getPossibleActions(){
	return m_unitPossibleActionFlags;
}

//Returns stack of directions, which is a path to target tile
std::stack<eDIRECTION> cUnit::getPathToTile(int p_nTargetTile, vec2D p_vMapSize){
	std::stack<eDIRECTION> pathStack;

	//check if tile is valid target
	if(not m_rangeMap.count(p_nTargetTile)){
		std::cout << "[ERROR] Tile is not valid target of movement" << std::endl;
		return pathStack;
	}

	int nDistance = m_rangeMap[p_nTargetTile];			//Load distance
	int nCurrentTile = p_nTargetTile;				//Set starting tile 

	//Look for tile with smaller distance untill distance to unit is zero
	while(nDistance > 0){
		//Surrounding tiles
		const int NORTH_TILE = nCurrentTile - p_vMapSize.x;
		const int SOUTH_TILE = nCurrentTile + p_vMapSize.x;
		const int EAST_TILE = nCurrentTile + 1;
		const int WEST_TILE = nCurrentTile - 1;

		//Look if tile is in range and with shorter path
		if(m_rangeMap.count(NORTH_TILE) and m_rangeMap[NORTH_TILE] < m_rangeMap[nCurrentTile]){
			pathStack.push(eDIRECTION::SOUTH);
			//Set new tile as curently checked tile
			nCurrentTile = NORTH_TILE;
		}
		else if(m_rangeMap.count(SOUTH_TILE) and m_rangeMap[SOUTH_TILE] < m_rangeMap[nCurrentTile]){
			pathStack.push(eDIRECTION::NORTH);
			//Set new tile as curently checked tile
			nCurrentTile = SOUTH_TILE;

		}
		else if(m_rangeMap.count(EAST_TILE) and m_rangeMap[EAST_TILE] < m_rangeMap[nCurrentTile]){
			pathStack.push(eDIRECTION::WEST);
			//Set new tile as curently checked tile
			nCurrentTile = EAST_TILE;
		}
		else if(m_rangeMap.count(WEST_TILE) and m_rangeMap[WEST_TILE] < m_rangeMap[nCurrentTile]){
			pathStack.push(eDIRECTION::EAST);
			//Set new tile as curently checked tile
			nCurrentTile = WEST_TILE;
		}
		else{
			std::cout << "[ERROR] Cannot determine proper path, returning empty path" << std::endl;
			//empty stack
			while(not pathStack.empty()){
				pathStack.pop();
			}
			return pathStack;
		}
		//Load new distance
		nDistance = m_rangeMap[nCurrentTile];
	}

	//Return stack with path 
	return pathStack;
}

//Calculate range
void cUnit::calculateRange(const std::vector<sTile> &p_tileVector, const std::set<int>& p_blockedTilesSet, vec2D p_vMapSize){
	//Create stack and push first position onto it
	std::stack<int>	stackOfTiles;
	stackOfTiles.push(m_vPos.x + (m_vPos.y * p_vMapSize.x));

	//Clear range map and place first tile onto it
	m_rangeMap.clear();
	m_rangeMap[m_vPos.x + (m_vPos.y * p_vMapSize.x)] = 0;

	//One line of difrence for easier calculation
	const int oneLine = p_vMapSize.x;

	//Vector holding tiles type Id for bordering tiles 
	std::vector<int> TILES;

	//Calculate range
	while(not stackOfTiles.empty()){
		//Set current tile
		const int CURRENT_TILE = stackOfTiles.top();

		//Clear vector of tiles from previous loop
		TILES.clear();

		//All tiles to check
		const int NORTH_TILE = stackOfTiles.top() - oneLine;
		const int SOUTH_TILE = stackOfTiles.top() + oneLine;
		const int EAST_TILE = stackOfTiles.top() + 1;
		const int WEST_TILE = stackOfTiles.top() - 1;

		//Check if tiles are within map
		if( not (NORTH_TILE < 0) ){
			TILES.push_back(NORTH_TILE);
		}
		if( not (SOUTH_TILE > (p_vMapSize.x * p_vMapSize.y) -1) ){
			TILES.push_back(SOUTH_TILE);
		}
		if( not (EAST_TILE / p_vMapSize.x != CURRENT_TILE / p_vMapSize.x) ){
			TILES.push_back(EAST_TILE);
		}
		if( not (WEST_TILE / p_vMapSize.x != CURRENT_TILE / p_vMapSize.x or WEST_TILE < 0) ){
			TILES.push_back(WEST_TILE);
		}

		//Flag for checking if new reachable tile was found
		bool bTileFound = false;

		//Check tiles
		for(size_t i = 0; i < TILES.size(); i++){	
			//Check if tile is in range and (if was not visisted or distance is shorther than previous visit)
			//And if not occupied by enemy team
			if(p_tileVector[TILES[i]].movCost + m_rangeMap[CURRENT_TILE] <= m_unitAttributes.mov
			and (!m_rangeMap.count(TILES[i]) 
			or m_rangeMap[TILES[i]] > m_rangeMap[CURRENT_TILE] + p_tileVector[CURRENT_TILE].movCost)
			and not p_blockedTilesSet.count(TILES[i]))
			{
				//Add tile to map with shortest known distance
				m_rangeMap[TILES[i]] = p_tileVector[TILES[i]].movCost + m_rangeMap[CURRENT_TILE];
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
	SDL_Rect srcRect = {0, 0, TILE_SIZE, TILE_SIZE};
	SDL_Rect dstRect = {0, 0, TILE_SIZE, TILE_SIZE};

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
	for(size_t i = 0; i < m_rangeVector.size(); i++){
		dstRect.x = m_rangeVector[i].x * TILE_SIZE + p_vCameraOffset.x;
		dstRect.y = m_rangeVector[i].y * TILE_SIZE + p_vCameraOffset.y;
		SDL_RenderCopy(g_renderer, m_pRangeTile, &srcRect, &dstRect);
	}
}
