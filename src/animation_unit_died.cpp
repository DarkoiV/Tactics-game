#include "animation_unit_died.hpp"
#include "globals.hpp"

// Constructor
cAnimationUnitDied::cAnimationUnitDied(const std::string& p_unitName) {
	textToDisplay = "UNIT " + p_unitName + " HAS DIED";
	m_text.update(textToDisplay);

	// Measure text to display
	const int width  = m_text.getPixelWidth();
	const int height = m_text.getPixelHeight();

	m_text.setOriginPoint({SCREEN_WIDTH/2 - width/2
		, SCREEN_HEIGHT/2 - height/2});
	
	// Set first letter visible
	m_displayedletters = 1;
	m_text.update(textToDisplay.substr(0, m_displayedletters));

	// Set how many frames it is going to take
	m_framesToDisplay = NEW_CHAR_DELAY * textToDisplay.size() + 60;
}

// Draw text to screen
void cAnimationUnitDied::draw() {
	m_text.draw();

	m_animationFrame++;
	if(m_animationFrame % NEW_CHAR_DELAY == 0) {
		m_displayedletters++;
		m_text.update(textToDisplay.substr(0, m_displayedletters));
	}
}

// Check if completed
bool cAnimationUnitDied::isCompleted() {
	return m_animationFrame > m_framesToDisplay;	
}
