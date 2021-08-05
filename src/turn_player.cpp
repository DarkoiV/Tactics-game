#include "turn_player.hpp"
#include "board.hpp"
#include "cursor.hpp"
#include "team.hpp"
#include "ui_collection.hpp"
#include "commander.hpp"

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
			if( selectedUnit.getPosition() == cursor.position() 
			or ( selectedUnit.range().inRange( board, cursor.position())
			and not playerTeam.isAnyHere(cursor.position(), nullptr)) ) {
				// Get path to selected position
				auto path = selectedUnit.range().getPath(board, cursor.position());

				// Create move commands to destination
				commander.moveUnit(&selectedUnit, path);

				// TMP switch to SELECT UNIT MODE
				m_mode = SELECT_ACTION;
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
	// Get selected unit
	auto &selectedUnit = playerTeam.selected();

	// Draw menu
	UI.aMenu[&selectedUnit];

	// Process input
	switch (p_input) {
		case eBUTTON::UP:
			UI.aMenu.moveUp();
			break;

		case eBUTTON::DOWN:
			UI.aMenu.moveDown();
			break;

		case eBUTTON::SELECT:
			{
				// Get selected action
				auto selectedAction = UI.aMenu.getSelectedAction();

				// ON WAIT
				if (selectedAction == "Wait") {
					selectedUnit.toggleActive(false);
					playerTeam.toggleMoveRange(false);

					UI.aMenu[nullptr];
					m_mode = POST_ACTION;
				}

				// ON ATTACK
				if (selectedAction == "Attack") {
					selectedUnit.range().calculateActionRange(board, 1, 1);
					playerTeam.toggleMoveRange(false);
					playerTeam.toggleActionRange(true);

					UI.aMenu[nullptr];
					m_mode = SELECT_TARGET;
				}
					
			}
			break;

		// TODO Revert position, switch to move unit mode
		case eBUTTON::CANCEL:
			break;

		// No input or unrecognized
		default:
		case eBUTTON::NONE:
			break;
	}
}

// SELECT TARGET MODE ////////////////////////////////////////////////////

void cTurnPlayer::processSelectTarget(eBUTTON p_input) {
	// Get selected unit
	auto &selectedUnit = playerTeam.selected();

	// Process input
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

		// Check if enemy is there, attack if so
		case eBUTTON::SELECT:
			{
				cUnit *enemyUnit = nullptr; 
				if (enemyTeam.isAnyHere(cursor.position(), &enemyUnit)
				and selectedUnit.range().inActionRange(board, cursor.position()) ) {
					// Create command of attack
					commander.attack(&selectedUnit, enemyUnit);

					playerTeam.toggleActionRange(false);
					cursor.toggleHiden(true);
					m_mode = POST_ACTION;
				}
			}
			break;

		// Switch back to SELEC ACTION MODE
		case eBUTTON::CANCEL:
			playerTeam.toggleActionRange(false);
			playerTeam.toggleMoveRange(true);
			
			m_mode = SELECT_ACTION;
			break;

		// No input or unrecognized
		default:
		case eBUTTON::NONE:
			break;
	}
}

// POST ACTION CHECKUP ////////////////////////////////////////////////////

void cTurnPlayer::processPostAction() {
	// Get selected unit
	auto &selectedUnit = playerTeam.selected();

	cursor.toggleHiden(false);

	selectedUnit.toggleActive(false);
	playerTeam.deselectUnit();

	// Check for dead unit, and remove them from scene
	playerTeam.checkDeadUnits(commander);
	enemyTeam.checkDeadUnits(commander);
	
	// TODO check if any unit reamined active
	
	// Recalc ranges
	playerTeam.calculateRange(board, enemyTeam);

	m_mode = SELECT_UNIT;
}

// PUBLIC METHODS ////////////////////////////////////////////////////////

// Start turn
void cTurnPlayer::start(){
	// Turn start in select unit mode! 
	m_mode = SELECT_UNIT;

	// Calculate ranges, and reset inactive of opposingTeam
	playerTeam.calculateRange(board, enemyTeam);
	enemyTeam.resetActiveStatus();
}

// Return turn status
auto cTurnPlayer::status() -> eTURN_STATUS{
	// TMP always return in progress
	return eTURN_STATUS::IN_PROGRESS;
}

// Process input, update turn
void cTurnPlayer::update(eBUTTON p_input) {
	
	// Check if any unit is under cursor and change cursor state
	cUnit* unitUnderCursor = nullptr;
	if	(playerTeam.isAnyHere(cursor.position(), &unitUnderCursor)) 	cursor[eCURSOR_MODE::ALLY];
	else if	(enemyTeam.isAnyHere(cursor.position(), &unitUnderCursor)) 	cursor[eCURSOR_MODE::ENEMY];
	else 									cursor[eCURSOR_MODE::NORMAL];
	UI.qStats[unitUnderCursor];
	
	// Check commander queue, 
	// If all commands completed, jump to current mode
	if( not commander.execute() ) {
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

			case POST_ACTION:
				processPostAction();
				break;
		}
	}
}
