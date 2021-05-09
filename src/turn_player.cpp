#include "turn_player.hpp"

// Init turn variables
void cTurnPlayer::init(vec2D p_boardSize){
	m_cursor.init(p_boardSize);
}

// Start turn
void cTurnPlayer::start(){
}

// Check if completed
bool cTurnPlayer::isCompleted(){

	// TMP
	return false;
}

// Process input
void cTurnPlayer::process(eBUTTON p_input){

	switch (p_input) {
		case eBUTTON::UP:
			m_cursor.moveUp();
			break;

		case eBUTTON::DOWN:
			m_cursor.moveDown();
			break;

		case eBUTTON::LEFT:
			m_cursor.moveLeft();
			break;
			
		case eBUTTON::RIGHT:
			m_cursor.moveRight();
			break;

		case eBUTTON::SELECT:
			break;

		// No input
		default:
		case eBUTTON::NONE:
			break;
	}
}

// Update 
void cTurnPlayer::update(){

}

// Draw turn entities
void cTurnPlayer::draw(vec2D p_cameraOffset, int p_animationFrame){
	m_cursor.draw(p_cameraOffset, p_animationFrame);
}
