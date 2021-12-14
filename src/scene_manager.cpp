#include "scene_manager.hpp"
#include "scene_battle.hpp"

void cSceneManager::loadScene(const eSCENE_TYPE p_type) {
	switch (p_type)	{
		case eSCENE_TYPE::SCENE_BATTLE_PVP:
			m_currentScene = std::make_unique<cSceneBattle>();
	}
}

auto cSceneManager::currentScene() const -> cScene* {
	return m_currentScene.get();
}
