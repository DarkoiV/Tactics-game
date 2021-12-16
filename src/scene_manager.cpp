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

	// Reset request status
	m_wasRequested = false;
}

void cSceneManager::nextScene(const eSCENE_TYPE p_type) {
	m_requested = p_type;
	m_wasRequested = true;
}

void cSceneManager::switchScene() {
	if(m_wasRequested) loadScene(m_requested);
	else loadScene(eSCENE_TYPE::MAIN_MENU);
}

auto cSceneManager::currentScene() const -> cScene* {
	return m_currentScene.get();
}
