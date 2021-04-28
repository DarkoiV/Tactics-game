#pragma once

#include "globals.hpp"
#include <SDL2/SDL.h>

class cGame{
	private:
		bool m_running = false;

	public:
		// Init game
		cGame();

		// Quit game
		~cGame();

		// Run game
		void operator()();
};
