#include "animator.hpp"
#include "animation_text.hpp"

// Draw all animations
void cAnimator::draw() {
	for (size_t i = 0; i < m_animations.size(); i++) {
		m_animations[i]->draw();

		// Delete completed animations
		if(m_animations[i]->isCompleted()) {
			m_animations.erase(m_animations.begin() + i);
			i--;
		}
	}
}

// Draw text to screen
void cAnimator::animateText(const std::string &p_text, eTEXT_COLOR p_color, int p_scale) {
	m_animations.push_back(std::make_unique<cAnimationText>(
		p_text, p_color, p_scale
	));

}
