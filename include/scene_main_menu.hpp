#pragma once

#include "scene.hpp"
#include "ui_text.hpp"
#include "ui_box.hpp"

#include <vector>

class cSceneManager;

class cSceneMainMenu: public cScene {

		cSceneManager& sceneManager;

		std::vector<cText> m_selection;
		uint m_selected = 0;
		
		cBox m_box;

		bool m_completed = false;

	public:
		cSceneMainMenu(cSceneManager& sm);

		void command(const std::string& p_command) override;
		bool completed() override { return m_completed; };

		void update(eBUTTON p_INPUT) override;
		void draw() override;
};
