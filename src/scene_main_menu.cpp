#include "scene_main_menu.hpp"
#include "globals.hpp"
#include "scene_manager.hpp"

using eSCENE_TYPE = cSceneManager::eSCENE_TYPE;

cSceneMainMenu::cSceneMainMenu(cSceneManager& sm): sceneManager(sm) {

	// PvP Battle
	m_selection.emplace_back( cText({0,0}, eTEXT_COLOR::YELLOW, 2) );
	m_selection.back().update("PvP Battle");

	// Exit
	m_selection.emplace_back( cText({0,0}, eTEXT_COLOR::YELLOW, 2) );
	m_selection.back().update("Exit");

	// Get widest text
	int widestText = 0;
	for(auto& text : m_selection) {
		if(widestText < text.getPixelWidth())
			widestText = text.getPixelWidth();
	}

	// Set box
	int textHeight = m_selection.back().getPixelHeight();
	int boxInnerHeight = (textHeight + 2) * m_selection.size();

	m_box.setCapacity({widestText, boxInnerHeight}, 5);
	m_box.setOrigin({0, -100});

	//Set text orgins
	vec2D textOrigin = m_box.getInnerOrigin();
	for(auto& text: m_selection) {
		text.setOriginPoint(textOrigin);
		textOrigin.y += textHeight + 2;
	}

	m_selection[0].changeTextColor(eTEXT_COLOR::RED);
}

void cSceneMainMenu::command(const std::string &p_command) {
	std::cout << "[WARN] Main menu does not accept commands " << p_command << " ignored" << std::endl;
}

void cSceneMainMenu::update(eBUTTON p_INPUT) {

	switch(p_INPUT) {
		case eBUTTON::UP:
			if(m_selected > 0) {
				m_selection[m_selected].changeTextColor(eTEXT_COLOR::YELLOW);
				m_selected--;
				m_selection[m_selected].changeTextColor(eTEXT_COLOR::RED);
			}
			break;

		case eBUTTON::DOWN:
			if(m_selected < m_selection.size() - 1) {
				m_selection[m_selected].changeTextColor(eTEXT_COLOR::YELLOW);
				m_selected++;
				m_selection[m_selected].changeTextColor(eTEXT_COLOR::RED);
			}
			break;

		case eBUTTON::SELECT:
		case eBUTTON::SPECIAL1:
			switch(m_selected) {
				// PvP Battle
				case 0:
					m_completed = true;
					sceneManager.nextScene(eSCENE_TYPE::BATTLE_PVP);
					break;

				// Exit
				case 1:
					SDL_Event quit;
					quit.type = SDL_QUIT;
					SDL_PushEvent(&quit);
					break;
			};
			break;
		
		default:
			break;
	}
	
}

void cSceneMainMenu::draw() {
	m_box.draw();
	for(const auto& text : m_selection) text.draw();
}
