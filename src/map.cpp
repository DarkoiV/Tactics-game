#include "map.hpp"

//Constructor
cMap::cMap(std::string p_mapName){
	std::cout << "[INFO] Creating map: " << p_mapName << std::endl;
	//If map is test map, fill vector with ID 1
	if(p_mapName == "testMap"){
		//Load plains tileset
		m_tilesetSprite = loadSprite("graphics/PlainsTileset.png");
		//Create size
		m_vSize.x = 30;
		m_vSize.y = 25;
		//Populare tiles
		for(int y = 0; y < m_vSize.y; y++){
			for(int x = 0; x < m_vSize.x; x++){
				sTile createdTile;
				createdTile.typeID = (x+y) % 2;
				createdTile.x = x;
				createdTile.y = y;
				m_tilesVector.push_back(createdTile);
			}
		}
		//In test map start in edit mode by default
		m_mapState = eMAP_STATE::EDIT_MODE;
	}

	//Print in console tiles representation
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
}

//Update new turn
void cMap::updateNewTurn(){
}

//Update edit mode
void cMap::updateEditMode(eBUTTON p_INPUT){
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
}
