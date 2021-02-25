#include "ui_box.hpp"

//Constructor
cBox::cBox(){
	//Load pointer for asset
	auto& assets = cAssetManager::getInstance();
	m_pBoxSprite = assets.getSprite("box");
	m_pBoxBackgroundSprite = assets.getSprite("boxBackground");

	//Set dimensions for box cell
	if (SDL_QueryTexture(m_pBoxSprite, NULL, NULL, &m_vTileSize.x, &m_vTileSize.y) != 0)
		std::cout << "[ERROR] Box couldn't get texture dimensions: " << SDL_GetError() << std::endl;

	//Calculate tile size based on texture
	m_vTileSize.x = m_vTileSize.x/3;
	m_vTileSize.y = m_vTileSize.y/3;

	//Set default stats
	m_vOriginPoint = {30, 30};
	m_vNoOfTiles = {7, 7};
}

//Set size in tiles
void cBox::setSize(vec2D p_vNoOfTiles){
	std::cout << "[INFO] Box tiles " << p_vNoOfTiles << std::endl;
	m_vNoOfTiles = p_vNoOfTiles;
}

//Set capacity
void cBox::setCapacity(vec2D p_vInnerSize){
	std::cout << "[INFO] Setting capacity size of at lest " << p_vInnerSize << " pixels" << std::endl;
	vec2D newBoxSize;

	//Set size x
	newBoxSize.x = (p_vInnerSize.x / m_vTileSize.x) + 2;

	//Set size y
	newBoxSize.y = (p_vInnerSize.y / m_vTileSize.y) + 2;

	setSize(newBoxSize);
}

//Get inner orgin
vec2D cBox::getInnerOrgin(){
	return { m_vOriginPoint.x + m_vTileSize.x, m_vOriginPoint.y + m_vTileSize.y };
}

//Get inner line width
int cBox::getInnerLineLenght(){
	return (m_vNoOfTiles.x - 2) * m_vTileSize.x;
}

//Set position of box
void cBox::setPosition(vec2D p_vPos){
	std::cout << "[INFO] Box new orgin point " << p_vPos << std::endl;
	m_vOriginPoint = p_vPos;
}

//Center box on screen
void cBox::centerBox(){
	std::cout << "[INFO] Box position set centered" << std::endl;

	vec2D newOrginPoint;
	newOrginPoint.x = g_windowWidth/2 - (m_vNoOfTiles.x * m_vTileSize.x)/2;
	newOrginPoint.y = g_windowHeight/2 - (m_vNoOfTiles.y * m_vTileSize.y)/2;

	setPosition(newOrginPoint);
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
