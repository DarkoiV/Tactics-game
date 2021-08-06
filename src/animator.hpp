#pragma once

#include "animation.hpp"

#include <vector>
#include <memory>

class cAnimator {
	private:
		// All animations
		std::vector<std::unique_ptr<cAnimation>> m_animations;

	public:
		// Draw all animations
		void draw();

		// Draw info about killed unit
		void unitDied(const std::string& p_name);
};