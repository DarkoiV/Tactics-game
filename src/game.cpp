#include "game.hpp"

// Constructor inits game
cGame::cGame(){
	// Set flag for game running 
	m_running = true;

	// Init SDL2
	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		// Err msg
		m_running = false;
		return;
	}
}

// Destructor quits game
cGame::~cGame(){
}

// Operator() runs game
void cGame::operator()(){
	// Game loop
	while(m_running){

	}
}
