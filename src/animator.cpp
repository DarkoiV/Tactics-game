#include "animator.hpp"
#include "animation_text.hpp"

void cAnimator::draw(vec2D p_cameraOffset) {
	for (size_t i = 0; i < m_animations.size(); i++) {
		m_animations[i]->draw(p_cameraOffset);

		// Delete completed animations
		if(m_animations[i]->isCompleted()) {
			m_animations.erase(m_animations.begin() + i);
			i--;
		}
	}
}

void cAnimator::animateText(const std::string &p_text, eTEXT_COLOR p_color, int p_scale) {
	m_animations.push_back(std::make_unique<cAnimationText>(
		p_text, p_color, p_scale
	));

}

void cAnimator::animateEffect(const vec2D p_pos, cAnimationEffect::eTYPE p_type) {
	m_animations.push_back(std::make_unique<cAnimationEffect>(
		p_pos, p_type
	));
}
