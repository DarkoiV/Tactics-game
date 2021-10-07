#pragma once

#include "animation.hpp"
#include "ui_text.hpp"

#include <string>

class cAnimationText : public cAnimation {
	private:
		cText m_text;

		std::string m_textToDisplay;

		int m_animationFrame = 0;
		int m_displayedletters = 0;
		int m_framesToDisplay;

		constexpr static int NEW_CHAR_DELAY = 3;

	public:
		cAnimationText(const std::string& p_text, eTEXT_COLOR p_color, int p_scale);

		// Animation methods
		void draw(vec2D p_cameraOffset) override;
		bool isCompleted() 		override;

};
