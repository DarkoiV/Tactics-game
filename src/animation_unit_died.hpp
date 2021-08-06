#pragma once

#include "animation.hpp"
#include "ui_text.hpp"

#include <string>

class cAnimationUnitDied : public cAnimation {
	private:
		cText m_text = cText({0, 0}, eTEXT_COLOR::RED, 3);

		std::string textToDisplay;

		int m_animationFrame = 0;
		int m_displayedletters = 0;
		int m_framesToDisplay;

		const int NEW_CHAR_DELAY = 3;

	public:
		cAnimationUnitDied(const std::string& p_unitName);

		// Animation methods
		void draw() 		override;
		bool isCompleted() 	override;

};
