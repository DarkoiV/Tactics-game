#include "scene_battle.hpp"

// Constructor 
cSceneBattle::cSceneBattle(){

	// Load board map
	m_board.load("TEST");

	// Start player turn
	m_turnVector.push_back(&m_playerTurn);
	currentTurn()->start();

}

// Destructor
cSceneBattle::~cSceneBattle(){

}

// TURN METHODS ////////////////////////////////////////////////////////////

// Get current turn
auto cSceneBattle::currentTurn() -> cTurn*{
	return m_turnVector[0];
}

// Switch to next turn
void cSceneBattle::nextTurn(){
}

// GAME LOOP METHODS ///////////////////////////////////////////////////////

// Process input
void cSceneBattle::process(eBUTTON p_input){

	// Process turn related input
	currentTurn()->process(p_input);
}

// Update scene
void cSceneBattle::update(){

	// Update turn
	currentTurn()->update();

	// Check if is completed
	if(currentTurn()->isCompleted()){
		// If so, switch to next turn
		nextTurn();
		currentTurn()->start();
	}

}

// Draw scene
void cSceneBattle::draw(){

	// Draw board
	m_board.draw(m_cameraOffset);

	// Draw turn components
	currentTurn()->draw(m_cameraOffset);
}
