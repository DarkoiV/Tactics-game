#pragma once

#include "scene.hpp"
#include "enums.hpp"
#include "scene_battle.hpp"
#include "ui_text.hpp"
#include <vector>

class cGame{
	private:
		// Game state
		bool    m_running      = false  ;
		cScene* m_currentScene = nullptr;
		
		// Console command
		std::string m_command = "";
		cText* m_consoleText = nullptr; 	// Has to be init after SDL!

		// Private methods
		bool    loadSettings();
		void    createFrame();
		void    drawConsole();
		eBUTTON getInput();

	public:
		// Init game
		cGame();

		// Free resources
		void freeResources();

		// Quit game
		~cGame();

		// Run game
		void operator()();
};
