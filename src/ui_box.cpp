#include "ui_box.hpp"
#include "asset_manager.hpp"
#include "globals.hpp"

// Constructor loads sprites, and sprite data
cBox::cBox(){
	// Load sprites
	auto assets = cAssetManager::getInstance();
	m_borderSprite = assets.getSprite("Box", "box_border");
	m_backgroundSprite = assets.getSprite("Box", "box_background");

	// Get lenght of tile edge
	SDL_QueryTexture(m_borderSprite, NULL, NULL, &m_boxTileEdge.x, &m_boxTileEdge.y);
	m_boxTileEdge.x = m_boxTileEdge.x / TILES_IN_LINE;
	m_boxTileEdge.y = m_boxTileEdge.y / TILES_IN_LINE;
}

// Set size based on needed capacity of box
void cBox::setCapacity(vec2D p_size, int p_margin){
	m_size.x = p_size.x + (p_margin * 2) + (m_boxTileEdge.x * 2);
	m_size.y = p_size.y + (p_margin * 2) + (m_boxTileEdge.y * 2);
	m_margin = p_margin;

	std::cout << "[INFO] Created box size is " << m_size << std::endl;
}

// Set origin point
void cBox::setOrigin(vec2D p_originPoint){
	// X axis
	if (p_originPoint.x < 0)	m_originPoint.x = SCREEN_WIDTH - (m_size.x - p_originPoint.x);
	else if (p_originPoint.x == 0)	m_originPoint.x = SCREEN_WIDTH/2 - (m_size.x/2);
	else 				m_originPoint.x = p_originPoint.x;

	// Y axis
	if (p_originPoint.y < 0)	m_originPoint.y = SCREEN_HEIGHT - (m_size.y - p_originPoint.y);
	else if (p_originPoint.y == 0)	m_originPoint.y = SCREEN_HEIGHT/2 - (m_size.y/2);
	else 				m_originPoint.y = p_originPoint.y;

}

// Get inner origin
auto cBox::getInnerOrigin() -> vec2D {
	vec2D innerOriginPoint;

	innerOriginPoint.x = m_originPoint.x + m_boxTileEdge.x + m_margin;
	innerOriginPoint.y = m_originPoint.y + m_boxTileEdge.y + m_margin;
	std::cout << "[INFO] Origin point of inner box is " << innerOriginPoint << std::endl;

	return innerOriginPoint;
}

// DRAW A BOX ;)
void cBox::draw() {
	// Setup rectangles
	SDL_Rect srcRect, dstRect;
	srcRect.w = m_boxTileEdge.x;
	srcRect.h = m_boxTileEdge.y;
	
	int innerWidth  = m_size.x - (m_boxTileEdge.x * 2);
	int innerHeight = m_size.y - (m_boxTileEdge.y * 2);

	for(int y = 0; y < TILES_IN_LINE; y++){
		// Set src y
		srcRect.y = m_boxTileEdge.y * y;
		// Set dst y
		dstRect.y 
			= m_originPoint.y + (m_boxTileEdge.y * (y > 0)) + (innerHeight * (y > 1));
		// Set dst h
		dstRect.h
			= m_boxTileEdge.y * (y != 1) + innerHeight * (y == 1);

		for(int x = 0; x < TILES_IN_LINE; x++){
			// Set src x
			srcRect.x = m_boxTileEdge.x * x;
			// Set dst x
			dstRect.x 
				= m_originPoint.x + (m_boxTileEdge.x * (x > 0)) + (innerWidth * (x > 1));
			// Set dst w
			dstRect.w
				= m_boxTileEdge.x * (x != 1) + innerWidth * (x == 1);

			// Draw to screen
			SDL_RenderCopy(g_renderer, m_backgroundSprite, &srcRect, &dstRect);
			SDL_RenderCopy(g_renderer, m_borderSprite, &srcRect, &dstRect);

		}
	}
}
