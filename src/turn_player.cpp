#include "turn_player.hpp"
#include "scene_battle.hpp"

// SELECT UNIT MODE //////////////////////////////////////////////////////

void cTurnPlayer::processSelectUnit(cSceneBattle &scene, eBUTTON p_input){

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

		// Try to select unit in team, 
		// If succesed toogle move range drawing, 
		// And change to MOVE UNIT MODE
		case eBUTTON::SELECT:
			if( scene.pTeam().selectUnit(scene.cursor().position()) ){
				scene.pTeam().toggleMoveRange(true);
				m_mode = MOVE_UNIT;
			}
			break;

		// TODO:
		// Open menu
		case eBUTTON::ESCAPE:
		case eBUTTON::CANCEL:
			break;

		// No input or unrecognized
		default:
		case eBUTTON::NONE:
			break;
	}
}

// MOVE UNIT MODE ////////////////////////////////////////////////////////

void cTurnPlayer::processMoveUnit(cSceneBattle &scene, eBUTTON p_input){
	// Get selected unit
	auto &selectedUnit = scene.pTeam().selected();

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

		// Check if move is withing range
		// If so procced to move
		case eBUTTON::SELECT:
			if( selectedUnit.range().inRange(scene) ){
				selectedUnit.setPosition(scene.cursor().position());
				scene.pTeam().calculateRange(scene, scene.board().getPassableForUnit());
			}
			break;

		// Deselect unit
		// Go back to SELECT UNIT MODE
		case eBUTTON::CANCEL:
			scene.pTeam().deselectUnit();
			scene.pTeam().toggleMoveRange(false);
			m_mode = SELECT_UNIT;

		// No input or unrecognized
		default:
		case eBUTTON::NONE:
			break;
	}
}

// SELECT ACTION MODE ////////////////////////////////////////////////////

void cTurnPlayer::processSelectAction(cSceneBattle &scene, eBUTTON p_input){
}

// SELECT TARGET MODE ////////////////////////////////////////////////////

void cTurnPlayer::processSelectTarget(cSceneBattle &scene, eBUTTON p_input){
}

// PUBLIC METHODS ////////////////////////////////////////////////////////

// Start turn
void cTurnPlayer::start(cSceneBattle &scene){
	m_mode = SELECT_UNIT;

	// Calculate ranges
	scene.pTeam().calculateRange(scene, scene.board().getPassableForUnit());
}

// Check if completed
bool cTurnPlayer::isCompleted(cSceneBattle &scene){
	// TMP
	return false;
}

// Process input, update turn
void cTurnPlayer::update(cSceneBattle &scene, eBUTTON p_input){
	switch (m_mode) {
		case SELECT_UNIT:
			processSelectUnit(scene, p_input);
			break;

		case MOVE_UNIT:
			processMoveUnit(scene, p_input);
			break;

		case SELECT_ACTION:
			processSelectAction(scene, p_input);
			break;

		case SELECT_TARGET:
			processSelectTarget(scene, p_input);
			break;
	}
}
