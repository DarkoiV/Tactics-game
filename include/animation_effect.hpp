#pragma once

#include "struct_vec2D.hpp"
#include "animation.hpp"
#include <SDL2/SDL.h>

class cAnimationEffect : public cAnimation {
	public:
		enum class eTYPE {
			HEAL,
		};

	private:
		SDL_Texture* m_sprite;

		constexpr static int RFRAMES_PER_SFRAME = 6;	// Render frames per sprite frame
		constexpr static int FRAMES_IN_SPRITE = 8;
		
		int m_animationFrame = 0;
		int m_framesToDisplay = FRAMES_IN_SPRITE * RFRAMES_PER_SFRAME;

		vec2D m_pos;

	public:
		cAnimationEffect(vec2D p_pos, eTYPE p_type);

		// Animation methods
		void draw(vec2D p_cameraOffset)	override;
		bool isCompleted()		override;
};
