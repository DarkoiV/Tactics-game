#include "animator.hpp"

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
