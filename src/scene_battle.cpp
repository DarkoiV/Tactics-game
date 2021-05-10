#include "scene_battle.hpp"

// Constructor 
cSceneBattle::cSceneBattle(){
	// Load board map
	m_board.load("TEST");

	// Init cursor
	m_cursor.init(m_board.getSize());

	// Start player turn
	m_turnVector.push_back(&m_playerTurn);
	currentTurn()->start(*this);
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
	currentTurn()->process(*this, p_input);
}

// Update scene
void cSceneBattle::update(){
	// Update turn
	currentTurn()->update(*this);

	// Check if is completed
	if(currentTurn()->isCompleted(*this)){
		// If so, switch to next turn
		nextTurn();
		currentTurn()->start(*this);
	}

}

// Draw scene
void cSceneBattle::draw(){
	// Animation frame
	static int animationFrame;
	animationFrame++;
	animationFrame = animationFrame % 60;

	// Draw components
	m_board.draw(m_cameraOffset);
	m_cursor.draw(m_cameraOffset, animationFrame);
}

// GET COMPONENT METHODS ///////////////////////////////////////////////////

auto cSceneBattle::board() -> cBoard&{
	return m_board;
}

auto cSceneBattle::cursor() -> cCursor&{
	return m_cursor;
}
