#pragma once

#include "enums.hpp"
#include "ui_text.hpp"
#include "scene_manager.hpp"
#include <vector>

class cGame{
	private:
		// Game state
		bool          m_running = false;
		cSceneManager m_sceneManager;
		
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

		// Game loop
		void loop();

		// Quit game
		~cGame();

		// Run game
		void operator()();
};
