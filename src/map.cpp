#include "map.hpp"

//Constructor based on size
cMap::cMap(vec2D p_vSize){
	std::cout << "[INFO] Creating editor map" << std::endl;

	//Load plains tileset, for test map
	m_tilesetSprite = loadSprite("graphics/plainsTileset.png");

	//Create size
	m_vSize.x = p_vSize.x;
	m_vSize.y = p_vSize.y;

	//Pass size to cursor, and set position
	m_cursor.loadMapSize(m_vSize);
	m_cursor.setPosition({7, 7});

	//Populare tiles with 1 and 2
	for(int y = 0; y < m_vSize.y; y++){
		for(int x = 0; x < m_vSize.x; x++){
			sTile createdTile;
			createdTile.typeID = (x+y) % 2;
			createdTile.x = x;
			createdTile.y = y;
			m_tilesVector.push_back(createdTile);
		}
	}

	//Map for editor, start in edit mode by default
	m_mapState = eMAP_STATE::EDIT_MODE;

	//Print in console tile representation
	std::cout << "[INFO] Map tiles types IDs: " << std::endl;
	for(int y = 0; y < m_vSize.y; y++){
		std::cout << "Y:  |";
		for(int x = 0; x < m_vSize.x; x++){
			if(m_tilesVector[x + (y * m_vSize.x)].typeID < 10)
				std::cout <<  "0" << m_tilesVector[x + (y * m_vSize.x)].typeID << "|"; 
			else
				std::cout << m_tilesVector[x + (y * m_vSize.x)].typeID << "|";
		}
		std::cout << std::endl;
	}

}

//Constructor that loads from file
cMap::cMap(std::string p_mapName){
}

//Destructor
cMap::~cMap(){
	//Free tileset texture
	SDL_DestroyTexture(m_tilesetSprite);
}

//Update map
void cMap::update(eBUTTON p_INPUT){
	switch (m_mapState) {
		case eMAP_STATE::NEW_TURN:
			updateNewTurn();
			break;
		case eMAP_STATE::EDIT_MODE: 
			updateEditMode(p_INPUT); 
			break;
		case eMAP_STATE::NORMAL_MODE: 
			updateNormalMode(p_INPUT); 
			break;
		case eMAP_STATE::UNIT_MODE: 
			updateUnitMode(p_INPUT); 
			break;
		case eMAP_STATE::ENEMY_TURN: 
			updateEnemyTurn(); 
			break;
	}

	//Update animation frame counter
	m_nAnimationFrameCounter++;
	if(m_nAnimationFrameCounter == 60)
		m_nAnimationFrameCounter = 0;
}

//Update new turn
void cMap::updateNewTurn(){
}

//Update edit mode
void cMap::updateEditMode(eBUTTON p_INPUT){
	switch(p_INPUT){
		case eBUTTON::UP:
			m_cursor.movUp();
			break;
		case eBUTTON::DOWN:
			m_cursor.movDown();
			break;
		case eBUTTON::RIGHT:
			m_cursor.movRight();
			break;
		case eBUTTON::LEFT:
			m_cursor.moveLeft();
			 break;
		case eBUTTON::NONE:
		default:
			 break;
	}
}

//Update normal mode
void cMap::updateNormalMode(eBUTTON p_INPUT){
}

//Update unit mode
void cMap::updateUnitMode(eBUTTON p_INPUT){
}

//Update enemy turn
void cMap::updateEnemyTurn(){
}

//draw map
void cMap::draw(){
	//Rectangles for tile usage
	SDL_Rect srcRect = {0, 0, TILE_SIZE, TILE_SIZE};
	SDL_Rect dstRect = {0, 0, TILE_SIZE, TILE_SIZE};
	//Draw tiles
	for(int y = 0; y < m_vSize.y; y++){
		//Set Y placement
		dstRect.y = (y * TILE_SIZE) + m_vCameraOffset.y;
		for(int x = 0; x < m_vSize.x; x++){
			//Set X placement
			dstRect.x = (x*TILE_SIZE) + m_vCameraOffset.x;

			//chose tile from sprite
			srcRect.x = (m_tilesVector[x + (y * m_vSize.y)].typeID % TILESET_WIDTH) * TILE_SIZE;
			srcRect.y = (m_tilesVector[x + (y * m_vSize.y)].typeID / TILESET_WIDTH) * TILE_SIZE;

			//Render tile
			SDL_RenderCopy(g_renderer, m_tilesetSprite, &srcRect, &dstRect);
		}
	}

	//Draw cursor
	m_cursor.draw(m_nAnimationFrameCounter, m_vCameraOffset);
}
