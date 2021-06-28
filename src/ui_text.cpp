#include "ui_text.hpp"
#include "asset_manager.hpp"
#include "globals.hpp"

// Create console text
cText::cText(vec2D p_originPoint){
	// Set origin point
	m_originPoint = p_originPoint;

	// Access console sprite
	auto &assetAccess = cAssetManager::getInstance();
	m_textSprite = assetAccess.getSprite("Text", "text_console");

	// Set character size
	SDL_QueryTexture(m_textSprite, NULL, NULL,  &m_characterSize.x, &m_characterSize.y);
}

// Create color text
cText::cText(vec2D p_originPoint, eTEXT_COLOR p_color){
	// Set origin point
	m_originPoint = p_originPoint;

	// Name of sprite
	std::string spriteName;
	switch (p_color) {
		case eTEXT_COLOR::RED:
			spriteName = "text_red";
			break;

		case eTEXT_COLOR::YELLOW:
			spriteName = "text_yellow";
			break;
	}

	// Access color text sprite
	auto &assetAccess = cAssetManager::getInstance();
	m_textSprite = assetAccess.getSprite("Text", spriteName);

	// Set character size
	SDL_QueryTexture(m_textSprite, NULL, NULL,  &m_characterSize.x, &m_characterSize.y);
	m_characterSize.x = m_characterSize.x / CHARS_PER_ROW;
	m_characterSize.y = m_characterSize.y / CHARS_PER_COLUMN;
}

// Create scaled color text, use color text constructor
cText::cText(vec2D p_originPoint, eTEXT_COLOR p_color, int p_scale) : cText(p_originPoint, p_color){
	// Set scale
	m_scaleOfText = p_scale;
}

// Get height of sprite in pixels
int cText::getPixelHeight(){
	return m_characterSize.y * m_scaleOfText;
}

// Get width of sprite in pixels
int cText::getPixelWidth(){
	return m_characterSize.x * m_textToRender.size() * m_scaleOfText;
}

// Change color of displayed text
void cText::changeTextColor(eTEXT_COLOR p_color){
	std::cout << "[INFO] Changing color of text: ";

	// Name of sprite
	std::string spriteName;
	switch (p_color) {
		case eTEXT_COLOR::RED:
			spriteName = "text_red";
			break;

		case eTEXT_COLOR::YELLOW:
			spriteName = "text_yellow";
			break;
	}

	// Access color text sprite
	auto &assetAccess = cAssetManager::getInstance();
	m_textSprite = assetAccess.getSprite("Text", spriteName);
}

// Change origin point of text
void cText::setOriginPoint(vec2D p_originPoint){
	std::cout << "[INFO] Changed orgin point of text: " << p_originPoint << std::endl;
	m_originPoint = p_originPoint;
}

// Change text to render
void cText::update(const std::string p_newText){
	m_textToRender = p_newText;
}

// Draw text to screen
void cText::draw(){
	SDL_Rect srcRect = {0, 0, m_characterSize.x, m_characterSize.y};
	SDL_Rect dstRect = {
		m_originPoint.x, 
		m_originPoint.y, 
		m_characterSize.x * m_scaleOfText, 
		m_characterSize.y * m_scaleOfText
	};

	// Draw each char
	for(size_t i = 0; i < m_textToRender.size(); i++){
		srcRect.x = (m_textToRender[i] - 32) / CHARS_PER_COLUMN;
		srcRect.y = (m_textToRender[i] - 32) / CHARS_PER_ROW;

		dstRect.x = m_originPoint.x + (i * m_characterSize.x * m_scaleOfText);

		SDL_RenderCopy(g_renderer, m_textSprite, &srcRect, &dstRect);
	}
}
