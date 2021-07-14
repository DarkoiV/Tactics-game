#include "turn_player.hpp"
#include "board.hpp"
#include "cursor.hpp"
#include "team.hpp"
#include "unit_command_move.hpp"

// SELECT UNIT MODE //////////////////////////////////////////////////////

void cTurnPlayer::processSelectUnit(eBUTTON p_input){

	switch (p_input) {
		case eBUTTON::UP:
			cursor.moveUp();
			break;

		case eBUTTON::DOWN:
			cursor.moveDown();
			break;

		case eBUTTON::LEFT:
			cursor.moveLeft();
			break;
			
		case eBUTTON::RIGHT:
			cursor.moveRight();
			break;

		// Try to select unit in team, 
		// If succesed toogle move range drawing, 
		// And change to MOVE UNIT MODE
		case eBUTTON::SELECT:
			if( playerTeam.selectUnit(cursor.position()) ){
				playerTeam.toggleMoveRange(true);
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

void cTurnPlayer::processMoveUnit(eBUTTON p_input){
	// Get selected unit
	auto &selectedUnit = playerTeam.selected();

	switch (p_input) {
		case eBUTTON::UP:
			cursor.moveUp();
			break;

		case eBUTTON::DOWN:
			cursor.moveDown();
			break;

		case eBUTTON::LEFT:
			cursor.moveLeft();
			break;
			
		case eBUTTON::RIGHT:
			cursor.moveRight();
			break;

		// Check if move is withing range
		// If so send proper commands to unit
		case eBUTTON::SELECT:
			if( selectedUnit.range().inRange( board, cursor.position()) ){
				// Get path stack
				std::stack<eDIRECTION> directionsOfMov;
				directionsOfMov = playerTeam.selected().range().getPath(board, cursor.position());

				// Create move commands queue from path stack
				while( not directionsOfMov.empty() ){
					m_commandQueue.emplace(
							std::make_unique<cCommandMove>( &playerTeam.selected(), directionsOfMov.top() )
							);
					directionsOfMov.pop();
				}

				// TMP switch to SELECT UNIT MODE
				playerTeam.deselectUnit();
				playerTeam.toggleMoveRange(false);
				playerTeam.calculateRange(board, board.getPassableForUnit());
				m_mode = SELECT_UNIT;
			}
			break;

		// Deselect unit
		// Go back to SELECT UNIT MODE
		case eBUTTON::CANCEL:
			playerTeam.deselectUnit();
			playerTeam.toggleMoveRange(false);
			m_mode = SELECT_UNIT;

		// No input or unrecognized
		default:
		case eBUTTON::NONE:
			break;
	}
}

// SELECT ACTION MODE ////////////////////////////////////////////////////

void cTurnPlayer::processSelectAction(eBUTTON p_input){
}

// SELECT TARGET MODE ////////////////////////////////////////////////////

void cTurnPlayer::processSelectTarget(eBUTTON p_input){
}

// PUBLIC METHODS ////////////////////////////////////////////////////////

// Start turn
void cTurnPlayer::start(){
	// Turn start in select unit mode! 
	m_mode = SELECT_UNIT;

	// Calculate ranges
	playerTeam.calculateRange(board, board.getPassableForUnit());
}

// Check if completed
bool cTurnPlayer::isCompleted(){
	// TMP always return false
	return false;
}

// Process input, update turn
void cTurnPlayer::update(eBUTTON p_input){
	// Check command queue
	if(not m_commandQueue.empty()){
		m_commandQueue.front()->execute();

		if(m_commandQueue.front()->isCompleted()){
			m_commandQueue.pop();
		}
	}
	//If all commands completed, jump to current mode
	else{
		switch (m_mode) {
			case SELECT_UNIT:
				processSelectUnit(p_input);
				break;

			case MOVE_UNIT:
				processMoveUnit(p_input);
				break;

			case SELECT_ACTION:
				processSelectAction(p_input);
				break;

			case SELECT_TARGET:
				processSelectTarget(p_input);
				break;
		}
	}
}
