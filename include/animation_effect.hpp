#pragma once

#include "struct_vec2D.hpp"
#include "animation.hpp"
#include <SDL2/SDL.h>

class cAnimationEffect : public cAnimation {
	private:
		SDL_Texture* m_sprite;
		
		int m_animationFrame = 0;
		int m_framesToDisplay;

		vec2D p_pos;

	public:
		cAnimationEffect();

		// Animation methods
		void draw(vec2D p_cameraOffset)	override;
		bool isCompleted()		override;
};
