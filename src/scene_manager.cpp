#include "scene_manager.hpp"
#include "scene_battle.hpp"
#include "scene_main_menu.hpp"

void cSceneManager::loadScene(const eSCENE_TYPE p_type) {
	switch (p_type)	{
		case eSCENE_TYPE::MAIN_MENU:
			m_currentScene = std::make_unique<cSceneMainMenu>(*this);
			break;

		case eSCENE_TYPE::BATTLE_PVP:
			m_currentScene = std::make_unique<cSceneBattle>();
			break;
	}
}

void cSceneManager::nextScene(const eSCENE_TYPE p_type) {
	m_requested = p_type;
}

void cSceneManager::switchScene() {
	loadScene(m_requested);
}

auto cSceneManager::currentScene() const -> cScene* {
	return m_currentScene.get();
}
