#pragma once

#include "animation.hpp"
#include <SDL2/SDL.h>

class cAnimationEffect : public cAnimation {
	private:
		SDL_Texture* m_sprite;

	public:
		cAnimationEffect();

		// Animation methods
		void draw()		override;
		bool isCompleted()	override;
};
