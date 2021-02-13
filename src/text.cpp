#include "text.hpp"

//Constructor
cText::cText(const vec2D p_vOriginPoint){
	//Set origin point
	m_vOriginPoint = p_vOriginPoint;

	//For now use console text only
	cAssetManager& assets = cAssetManager::getInstance();
	m_pTextSprite = assets.getSprite("consoleText");

	//Get character dimensions
	SDL_QueryTexture(m_pTextSprite, NULL, NULL, &m_vCharacterSize.x, &m_vCharacterSize.y);
	m_vCharacterSize.x = m_vCharacterSize.x / CHARS_PER_ROW;
	m_vCharacterSize.y = m_vCharacterSize.y / CHARS_PER_COLUMN;
}

//Destructor
cText::~cText(){
}

//Update text to render
void cText::update(const std::string p_sNewText){
	m_sTextToRender = p_sNewText;
}

//Draw to screen
void cText::draw(){
	SDL_Rect srcRect = {0, 0, m_vCharacterSize.x, m_vCharacterSize.y};
	SDL_Rect dstRect = {m_vOriginPoint.x, 
			m_vOriginPoint.y, 
			m_vCharacterSize.x, 
			m_vCharacterSize.y};

	//Loop through string and render chars
	for(size_t i = 0; i < m_sTextToRender.size(); i++){
		//Select char from texture
		srcRect.x = ((m_sTextToRender[i] - 32) % CHARS_PER_ROW) * m_vCharacterSize.x;
		srcRect.y = ((m_sTextToRender[i] - 32) / CHARS_PER_ROW) * m_vCharacterSize.y;

		//Copy to screen
		SDL_RenderCopy(g_renderer, m_pTextSprite, &srcRect, &dstRect);

		//Move dst to next char
		dstRect.x +=  m_vCharacterSize.x;
	}
}
