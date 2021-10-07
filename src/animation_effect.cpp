#include "globals.hpp"
#include "animation_effect.hpp"
#include "asset_manager.hpp"

cAnimationEffect::cAnimationEffect(const vec2D p_pos, eTYPE p_type) {
	auto &assets = cAssetManager::getInstance();

	// Load sprite based on type
	switch(p_type) {
		case eTYPE::HEAL: 
			m_sprite = assets.getSprite("Animation", "effect_heal");
			break;
	}

	m_pos = p_pos;
}

void cAnimationEffect::draw(vec2D p_cameraOffset) {
	SDL_Rect srcRect = {
		(m_animationFrame / RFRAMES_PER_SFRAME) * TILE_SIZE,
		0,
		TILE_SIZE,
		TILE_SIZE
	};
	SDL_Rect dstRect = {
		(m_pos.x + p_cameraOffset.x) * TILE_SIZE,
		(m_pos.y + p_cameraOffset.y) * TILE_SIZE,
		TILE_SIZE,
		TILE_SIZE
	};
	SDL_RenderCopy(g_renderer, m_sprite, &srcRect, &dstRect);

	m_animationFrame++;
}

bool cAnimationEffect::isCompleted() {
	return m_animationFrame >= m_framesToDisplay;
}
