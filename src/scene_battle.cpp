#include "scene_battle.hpp"

// Constructor 
cSceneBattle::cSceneBattle(){
	// Load board map
	m_board.load("TEST");

}

// Destructor
cSceneBattle::~cSceneBattle(){

}

// Process input
void cSceneBattle::process(eBUTTON p_input){

}

// Update scene
void cSceneBattle::update(){

}

// Draw scene
void cSceneBattle::draw(){

	// Draw board
	m_board.draw(m_cameraOffset);
}
