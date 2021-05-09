#include "turn_player.hpp"
#include "scene_battle.hpp"

// Start turn
void cTurnPlayer::start(cSceneBattle &scene){

	switch (m_mode) {
		case SELECT_UNIT:
			break;
		
		case MOVE_UNIT:
			break;
			
		case SELECT_ACTION:
			break;

		case SELECT_TARGET:
			break;
	}
}

// Check if completed
bool cTurnPlayer::isCompleted(cSceneBattle &scene){

	// TMP
	return false;
}

// Process input
void cTurnPlayer::process(cSceneBattle &scene, eBUTTON p_input){

	switch (p_input) {
		case eBUTTON::UP:
			scene.cursor().moveUp();
			break;

		case eBUTTON::DOWN:
			scene.cursor().moveDown();
			break;

		case eBUTTON::LEFT:
			scene.cursor().moveLeft();
			break;
			
		case eBUTTON::RIGHT:
			scene.cursor().moveRight();
			break;

		case eBUTTON::SELECT:
			break;

		// No input or unrecognized
		default:
		case eBUTTON::NONE:
			break;
	}
}

// Update 
void cTurnPlayer::update(cSceneBattle &scene){

}
