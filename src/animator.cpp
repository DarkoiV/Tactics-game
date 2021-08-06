#include "animator.hpp"
#include "animation_unit_died.hpp"

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

void cAnimator::unitDied(const std::string &p_name) {
	m_animations.push_back(std::make_unique<cAnimationUnitDied>( 
		cAnimationUnitDied(p_name)
	));

}
