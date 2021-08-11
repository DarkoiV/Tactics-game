#include "animation_text.hpp"
#include "globals.hpp"

// Constructor
cAnimationText::cAnimationText(const std::string& p_text, eTEXT_COLOR p_color, int p_scale) : m_text({0,0}, p_color, p_scale) {
	m_textToDisplay = p_text;
	m_text.update(m_textToDisplay);

	// Measure text to display
	const int width  = m_text.getPixelWidth();
	const int height = m_text.getPixelHeight();

	m_text.setOriginPoint({SCREEN_WIDTH/2 - width/2
		, SCREEN_HEIGHT/2 - height/2});
	
	// Set first letter visible
	m_displayedletters = 1;
	m_text.update(m_textToDisplay.substr(0, m_displayedletters));

	// Set how many frames it is going to take
	m_framesToDisplay = NEW_CHAR_DELAY * m_textToDisplay.size() + 60;
}

// Draw text to screen
void cAnimationText::draw() {
	m_text.draw();

	m_animationFrame++;
	if(m_animationFrame % NEW_CHAR_DELAY == 0) {
		m_displayedletters++;
		m_text.update(m_textToDisplay.substr(0, m_displayedletters));
	}
}

// Check if completed
bool cAnimationText::isCompleted() {
	return m_animationFrame > m_framesToDisplay;	
}
