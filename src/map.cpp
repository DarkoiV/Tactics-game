#include "map.hpp"

//Constructor based on size
cMap::cMap(vec2D p_vSize){
	std::cout << "[INFO] Creating editor map" << std::endl;

	//Load plains tileset, for test map
	m_pTilesetSprite = loadSprite("graphics/plainsTileset.png");

	//Create size
	m_vSize.x = p_vSize.x;
	m_vSize.y = p_vSize.y;

	//Populare tiles with 1 and 2
	for(int y = 0; y < m_vSize.y; y++){
		for(int x = 0; x < m_vSize.x; x++){
			sTile createdTile;
			createdTile.typeID = (x+y) % 2;
			createdTile.movCost = 1;
			m_tilesVector.push_back(createdTile);
		}
	}
}

//Constructor that loads from file
cMap::cMap(std::string p_sMapName){
}

//Destructor
cMap::~cMap(){
	//Free tileset texture
	SDL_DestroyTexture(m_pTilesetSprite);
}

//Update map
void cMap::update(eBUTTON p_INPUT){
}

//Increase tile type 
void cMap::tileTypeIncrease(vec2D p_vTilePos){
	std::cout << "[INFO] Increased tile type at " << p_vTilePos << std::endl;
	m_tilesVector[p_vTilePos.x + (p_vTilePos.y * m_vSize.x)].typeID++;
}

//Decrease tile type
void cMap::tileTypeDecrease(vec2D p_vTilePos){
	if(m_tilesVector[p_vTilePos.x + (p_vTilePos.y * m_vSize.x)].typeID > 0){
		std::cout << "[INFO] Decreased tile type at " << p_vTilePos << std::endl;
		m_tilesVector[p_vTilePos.x + (p_vTilePos.y * m_vSize.x)].typeID--;
	}
	else
		std::cout << "[INFO] Can't have typeID below 0! " << std::endl;
}

//Copy tile type
int cMap::tileTypeCopy(vec2D p_vTilePos){
	std::cout << "Copied tile from " << p_vTilePos << std::endl;
	return m_tilesVector[p_vTilePos.x + (p_vTilePos.y * m_vSize.x)].typeID;
}

//Paste tile type
void cMap::tileTypepaste(vec2D p_vTilePos, int p_nType){
	std::cout << "Pasted tile type: " << p_nType << ", to position: " << p_vTilePos << std::endl;
	m_tilesVector[p_vTilePos.x + (p_vTilePos.y * m_vSize.x)].typeID = p_nType;
}

//Print tiles types
void cMap::printTilesTypes(){
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

//Reference map
const std::vector<sTile>& cMap::refMap(){
	return m_tilesVector;
}

//Get map size
vec2D cMap::getMapSize(){
	return m_vSize;
}

//Set tiles mov cost
void cMap::setTilesMovCost(){
	for(size_t i = 0; i < m_tilesVector.size(); i++){
		if(m_tilesVector[i].typeID > 5 and m_tilesVector[i].typeID < 24)
			m_tilesVector[i].movCost = 99;
		else
			m_tilesVector[i].movCost = 1;
	}
}

//draw map
void cMap::draw(vec2D p_vCameraOffset){
	//Rectangles for tile usage
	SDL_Rect srcRect = {0, 0, TILE_SIZE, TILE_SIZE};
	SDL_Rect dstRect = {0, 0, TILE_SIZE, TILE_SIZE};
	//Draw tiles
	for(int y = 0; y < m_vSize.y; y++){
		//Set Y placement
		dstRect.y = (y * TILE_SIZE) + p_vCameraOffset.y;
		for(int x = 0; x < m_vSize.x; x++){
			//Set X placement
			dstRect.x = (x*TILE_SIZE) + p_vCameraOffset.x;

			//chose tile from sprite
			srcRect.x = (m_tilesVector[x + (y * m_vSize.x)].typeID % TILESET_WIDTH) * TILE_SIZE;
			srcRect.y = (m_tilesVector[x + (y * m_vSize.x)].typeID / TILESET_WIDTH) * TILE_SIZE;

			//Render tile
			SDL_RenderCopy(g_renderer, m_pTilesetSprite, &srcRect, &dstRect);
		}
	}
}
