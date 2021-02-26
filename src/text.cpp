#include "text.hpp"

//Constructor for console text
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

//Constructor for colored text
cText::cText(const vec2D p_vOriginPoint, int p_nColor){
	//Set origin point
	m_vOriginPoint = p_vOriginPoint;
	
	//Sprite
	std::string spriteName = "textColor";
	spriteName += std::to_string(p_nColor);

	//Load correct color text sprite
	cAssetManager& assets = cAssetManager::getInstance();
	m_pTextSprite = assets.getSprite(spriteName);

	//Check if correct sprite loaded, set using color text true
	if(m_pTextSprite == nullptr)
		std::cout << "[ERROR] Wrong text sprite " << std::endl;
	else
		m_bUsingColorText = true;

	//Get character dimensions
	SDL_QueryTexture(m_pTextSprite, NULL, NULL, &m_vCharacterSize.x, &m_vCharacterSize.y);
	m_vCharacterSize.x = m_vCharacterSize.x / CHARS_PER_ROW;
	m_vCharacterSize.y = m_vCharacterSize.y / CHARS_PER_COLUMN;
}

//Destructor
cText::~cText(){
}

//Get text lenght in pixels
int cText::getTextLenght(){
	return m_sTextToRender.length() * m_vCharacterSize.x;
}

//Get text height in pixels
int cText::getTextHeight(){
	return m_vCharacterSize.y;
}

//Change color of displayed text
void cText::changeTextColor(int p_nColor){
	if(m_bUsingColorText){
		if(p_nColor <= 0 or p_nColor > m_nLastPossibleColor){
			std::cout << "[WARNING] This color is not available" << std::endl;
			return;
		}
		std::string spriteName = "textColor";
		spriteName += std::to_string(p_nColor);

		cAssetManager& assets = cAssetManager::getInstance();
		m_pTextSprite = assets.getSprite(spriteName);
	}
	else
		std::cout << "[WARNING] Console text doesn't have ability to change color" << std::endl;
}

//Set new origin point
void cText::setNewOriginPoint(vec2D p_vNewOriginPoint){
	std::cout << "[INFO] New origin point of text " << p_vNewOriginPoint << std::endl;
	m_vOriginPoint = p_vNewOriginPoint;
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
