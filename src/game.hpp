#pragma once

#include "scene.hpp"
#include "enums.hpp"
#include <vector>

class cGame{
	private:
		// Game state
		bool   m_running      = false         ;
		eSCENE m_currentScene = eSCENE::BATTLE;

		// Container of scenes pointers
		std::vector<cScene*> scenesVector;

	public:
		// Init game
		cGame();

		// Quit game
		~cGame();

		// Run game
		void operator()();
};
