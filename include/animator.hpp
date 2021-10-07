#pragma once

#include "animation.hpp"
#include "struct_vec2D.hpp"

#include <vector>
#include <memory>

enum class eTEXT_COLOR;

class cAnimator {
	private:
		// All animations
		std::vector<std::unique_ptr<cAnimation>> m_animations;

	public:
		// Draw all animations
		void draw(vec2D p_cameraOffset);

		// Draw info about killed unit
		void animateText(const std::string& p_text, eTEXT_COLOR p_color, int p_scale);
};
