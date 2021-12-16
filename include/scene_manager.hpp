#pragma once

#include "scene.hpp"

#include <memory>

class cSceneManager {
	private:
		std::unique_ptr<cScene> m_currentScene;

	public:
		// Scene types
		enum class eSCENE_TYPE {
			SCENE_MAIN_MENU,
			SCENE_BATTLE_PVP
		};

		// Load scene based on it's type
		void loadScene(const eSCENE_TYPE p_type);

		// Return current scene
		auto currentScene() const -> cScene*;
};
