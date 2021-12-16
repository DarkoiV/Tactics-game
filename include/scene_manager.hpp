#pragma once

#include "scene.hpp"

#include <memory>

class cSceneManager {
	public:
		// Scene types
		enum class eSCENE_TYPE {
			MAIN_MENU,
			BATTLE_PVP
		};

	private:
		std::unique_ptr<cScene> m_currentScene;

		// Load scene based on it's type
		void loadScene(const eSCENE_TYPE p_type);

		// Requested scene
		eSCENE_TYPE m_requested;
		bool m_wasRequested = false;

	public:

		// Request change of scene
		void nextScene(const eSCENE_TYPE p_type);

		// Switch to requested scene
		void switchScene();

		// Return current scene
		auto currentScene() const -> cScene*;
};
