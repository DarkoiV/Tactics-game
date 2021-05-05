#pragma once

#include "scene.hpp"
#include "enums.hpp"
#include "scene_battle.hpp"
#include <vector>

class cGame{
	private:
		// Game state
		bool    m_running      = false   ;
		cScene* m_currentScene = nullptr;

		// Private methods
		void    createFrame();
		eBUTTON getInput()   ;

	public:
		// Init game
		cGame();

		// Quit game
		~cGame();

		// Run game
		void operator()();
};
