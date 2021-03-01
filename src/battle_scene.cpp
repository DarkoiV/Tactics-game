#include "battle_scene.hpp"

//constructor for editor
cBattleScene::cBattleScene(vec2D p_vMapSize) : m_map(p_vMapSize){
	//Set boundaries and starting position for cursor
	m_cursor.loadMapSize(p_vMapSize);
	m_cursor.setPosition({7, 7});

	//start in new turn
	m_sceneMode = eSCENE_MODE::NEW_TURN;

	//TMP Add 2 units
	addAllyUnit("infantry");
	addAllyUnit("infantry");
	m_allyVector[1]->setPosition({10, 10});

}

//constructor loading from file
cBattleScene::cBattleScene(std::string p_sMapName) : m_map(p_sMapName){
}

//update camera 
void cBattleScene::updateCamera(){	
	switch(m_cameraMode){
		default:
		case eCAMERA::EDGE_SCROLLING:
			//Y axis
			if(m_cursor.getPosition().y * TILE_SIZE + m_vCameraOffset.y < 0){
				m_vCameraOffset.y += TILE_SIZE;
				std::cout << "[INFO] Moving camera up" << std::endl;
			}
			else if((m_cursor.getPosition().y + 1) * TILE_SIZE + m_vCameraOffset.y > g_windowHeight){
				m_vCameraOffset.y -= TILE_SIZE;
				std::cout << "[INFO Moving camera down" << std::endl;
			}
			//X axis
			if(m_cursor.getPosition().x * TILE_SIZE + m_vCameraOffset.x < 0){
				m_vCameraOffset.x += TILE_SIZE;
				std::cout << "[INFO] Moving camera right" << std::endl;
			}
			else if((m_cursor.getPosition().x + 1) * TILE_SIZE + m_vCameraOffset.x > g_windowWidth){
				m_vCameraOffset.x -= TILE_SIZE;
				std::cout << "[INFO Moving camera left" << std::endl;
			}
			break;
		case eCAMERA::CENTERED:
			break;
	}

}

//Updat occupied tiles
void cBattleScene::updateOccupiedTiles(){
	m_occupiedByAllySet.clear();
	m_occupiedByEnemySet.clear();

	for(auto &UNIT : m_allyVector)
		m_occupiedByAllySet.insert(UNIT->occupiesTile(m_map.getMapSize()));

	for(auto &UNIT : m_enemyVector)
		m_occupiedByEnemySet.insert(UNIT->occupiesTile(m_map.getMapSize()));
}

//Update ranges
void cBattleScene::updateRanges(){
	for(auto &UNIT : m_allyVector)
		UNIT->calculateRange(m_map.refMap(), m_occupiedByEnemySet, m_map.getMapSize());
	for(auto &UNIT : m_enemyVector)
		UNIT->calculateRange(m_map.refMap(), m_occupiedByAllySet, m_map.getMapSize());
}

//Update
void cBattleScene::update(eBUTTON p_INPUT){
	//Check for console input
	if(g_bConsoleCommandIssued)
		processConsoleCommand(g_sConsoleCommand);

	//Check if commands are processed, if so disable inputs
	if(m_commander.isProcessingCommands())
		p_INPUT = eBUTTON::NONE;
	
	//Call mode specific update method
	switch(m_sceneMode){
		//New Turn
		default:
		case eSCENE_MODE::NEW_TURN:
			startNewTurn();
			break;

		//Edit mode
		case eSCENE_MODE::EDIT_MAP:
			updateEdit(p_INPUT);
			break;

		//Player turn, move unit
		case eSCENE_MODE::PLAYER_TURN_NOTHING_SELECTED:
			nothingSelected(p_INPUT);
			break;

		//Player turn, move unit
		case eSCENE_MODE::PLAYER_TURN_SELECTED:
			unitSelected(p_INPUT);
			break;

		//Player turn, select action
		case eSCENE_MODE::PLAYER_TURN_ACTION:
			selectAction(p_INPUT);
			break;
	}

	//Update camera
	updateCamera();

	//Update animation frame counter
	m_nAnimationFrameCounter++;
	if(m_nAnimationFrameCounter == 60)
		m_nAnimationFrameCounter = 0;
}

///////////////////////EDIT MODE/////////////////////////////////////////////////////////////////////////////////////////////

//Update edit mode
void cBattleScene::updateEdit(eBUTTON p_INPUT){
	switch(p_INPUT){
		//Move cursor
		case eBUTTON::UP:
			m_cursor.movUp();
			break;
		case eBUTTON::DOWN:
			m_cursor.movDown();
			break;
		case eBUTTON::RIGHT:
			m_cursor.movRight();
			break;
		case eBUTTON::LEFT:
			m_cursor.moveLeft();
			break;
		//On select, select next tile
		case eBUTTON::SELECT:
			m_map.tileTypeIncrease(m_cursor.getPosition());
			break;
		//On cancel, select previous tile
		case eBUTTON::CANCEL:
			m_map.tileTypeDecrease(m_cursor.getPosition());
			break;
		//On special 1, copy
		case eBUTTON::SPECIAL:
			m_nCopiedTileID = m_map.tileTypeCopy(m_cursor.getPosition());
			break;
		//On special 2, paste
		case eBUTTON::SPECIAL2:
			m_map.tileTypepaste(m_cursor.getPosition(), m_nCopiedTileID);
			break;
		//TMP switch modes, later open menu
		case eBUTTON::ESCAPE:
			m_sceneMode = eSCENE_MODE::PLAYER_TURN_NOTHING_SELECTED;
			break;
		//On none(or not used input here), do nothing, lol
		case eBUTTON::NONE:
		default:
			 break;
	}

	//Update all tiles mov cost
	m_map.setTilesMovCost();
}

//Process issued command
void cBattleScene::processConsoleCommand(std::string p_sCommand){
	//Split string
	std::vector<std::string> arguments;
	std::string current_argument;
	std::stringstream commandStream(p_sCommand);
	while(getline(commandStream, current_argument, ' '))
			arguments.push_back(current_argument);

	//Process arguments
	if(arguments.size() < 1){
		std::cout << "[INFO] Empty command provided" << std::endl;
	}
	else if(arguments[0] == "spawn"){
		if(arguments.size() < 2){
			std::cout << "[WARNING] Not enough arguments for SPAWN" << std::endl;
		}
		else if(arguments[1] == "ally"){
			std::cout << "[INFO] Spawning ally unit" << std::endl;
			addAllyUnit("infantry");

			//Reset flag
			g_bConsoleCommandIssued = false;
		}
		else if(arguments[1] == "enemy"){
			std::cout << "[INFO] Sprawning enemy unit" << std::endl;
			addEnemyUnit("enemyInfantry");

			//Reset flag
			g_bConsoleCommandIssued = false;
		}
		else{
			std::cout << "[WARNING] Unknown spawn argument" << std::endl;
		}
	}
	else if(arguments[0] == "new_turn"){
		std::cout << "[INFO] starting new turn" << std::endl;
		m_nSelectedUnit = -1;
		m_sceneMode = eSCENE_MODE::NEW_TURN;
		m_actionMenu.hideActionMenu();

		//Reset flag
		g_bConsoleCommandIssued = false;
	}
}

//Add allied unit to map
void cBattleScene::addAllyUnit(std::string p_sUnitName){
	auto newUnit = std::make_shared<cUnit>(p_sUnitName);
	m_allyVector.push_back(newUnit);
	m_sortedUnitVector.push_back(newUnit);

	//Set position under the cursor
	newUnit->setPosition(m_cursor.getPosition());	
}

//Add enemy unit to map
void cBattleScene::addEnemyUnit(std::string p_sUnitName){
	auto newUnit = std::make_shared<cUnit>(p_sUnitName);
	m_enemyVector.push_back(newUnit);
	m_sortedUnitVector.push_back(newUnit);

	//Set position under the cursor
	newUnit->setPosition(m_cursor.getPosition());	
}

///////////////////////PLAYER TURN///////////////////////////////////////////////////////////////////////////////////////////

//Begining of new turn
void cBattleScene::startNewTurn(){
	m_nTurnCounter++;
	std::cout << "[INFO] Starting turn: " << m_nTurnCounter << std::endl;

	//Recalculate ranges and occupied tiles
	updateOccupiedTiles();
	updateRanges();

	//Reset units exhaustion status
	for(auto &UNIT : m_sortedUnitVector)
		UNIT->setNotExhausted();

	//Switch to player turn
	m_sceneMode = eSCENE_MODE::PLAYER_TURN_NOTHING_SELECTED;
}

//Behaviour when no unit was selected
void cBattleScene::nothingSelected(eBUTTON p_INPUT){
	switch(p_INPUT){
		//Move cursor
		case eBUTTON::UP:
			m_cursor.movUp();
			break;
		case eBUTTON::DOWN:
			m_cursor.movDown();
			break;
		case eBUTTON::RIGHT:
			m_cursor.movRight();
			break;
		case eBUTTON::LEFT:
			m_cursor.moveLeft();
			break;

		case eBUTTON::SELECT:
			//Check if there is allied unit under cursor, and if is not exhausted
			for(size_t i = 0; i < m_allyVector.size(); i++){
				if(m_allyVector[i]->isHere(m_cursor.getPosition()) 
				and m_allyVector[i]->isNotExhausted()){
					//If there is, set which one and change mode to unit selected
					std::cout << "[INFO] Selected unit" << std::endl;
					m_nSelectedUnit = i;
					m_sceneMode = eSCENE_MODE::PLAYER_TURN_SELECTED;
					break;
				}
			}
			break;

		//TMP Switch to edit mode. later open menu
		case eBUTTON::ESCAPE:
			m_sceneMode = eSCENE_MODE::EDIT_MAP;
			break;

		//Nothing
		case eBUTTON::NONE:
		default:
			break;
	}

}

//Move selected unit
void cBattleScene::unitSelected(eBUTTON p_INPUT){
	switch(p_INPUT){
		//Move cursor
		case eBUTTON::UP:
			m_cursor.movUp();
			break;
		case eBUTTON::DOWN:
			m_cursor.movDown();
			break;
		case eBUTTON::RIGHT:
			m_cursor.movRight();
			break;
		case eBUTTON::LEFT:
			m_cursor.moveLeft();
			break;
		
		//Move unit 
		case eBUTTON::SELECT:
			//Check if move is withing range and no allied unit blocks destination(and this unit is not himself, 
			//If so move unit
			if (getSelectedUnit()->isMoveInRange(m_cursor.highlightedTile()) 
				and ( m_occupiedByAllySet.count(m_cursor.highlightedTile()) == 0 
				or getSelectedUnit()->isHere(m_cursor.getPosition()))) {

				std::cout << "[INFO] Moving unit" << std::endl;

				//Load stack with directions for movement
				std::stack<eDIRECTION> pathStack; 
				pathStack = getSelectedUnit()->getPathToTile(m_cursor.highlightedTile(), m_map.getMapSize());
	
				//Translate stack to commands
				while(not pathStack.empty()){
					//Add command
					m_commander.moveUnit(getSelectedUnit(), pathStack.top());
					pathStack.pop();
				}
				
				//Switch to action turn mode
				m_sceneMode = eSCENE_MODE::PLAYER_TURN_ACTION;
			}
			break;

		case eBUTTON::CANCEL:
			//Deselect unit
			std::cout << "[INFO] Unit deselected" << std::endl;
			m_nSelectedUnit = -1;
			m_sceneMode = eSCENE_MODE::PLAYER_TURN_NOTHING_SELECTED;
			break;

		case eBUTTON::NONE:
		default:
			break;
	}
}

//Select action to perform after move
void cBattleScene::selectAction(eBUTTON p_INPUT){
	//Show action menu after all move commands were processed
	if(m_actionMenu.isHidden() and m_commander.noCommands())
		m_actionMenu.showActionMenu(getSelectedUnit()->getPossibleActions());

	//everything else do when menu is shown
	else if(not m_actionMenu.isHidden()){
		//Process input
		switch (p_INPUT){
			case eBUTTON::UP:
				m_actionMenu.movSelectionUP();
				break;

			case eBUTTON::DOWN:
				m_actionMenu.movSelectionDOWN();
				break;

			case eBUTTON::SELECT:
				//Hide menu and do things based on return from action menu
				m_actionMenu.hideActionMenu();
				switch (m_actionMenu.getSelectedAction()) {
					default:
					case eACTION::WAIT:
						//Set unit as inactive, deselect, and switch to player turn nothing selected
						getSelectedUnit()->setExhausted();
						m_nSelectedUnit = -1;
						m_sceneMode = eSCENE_MODE::PLAYER_TURN_NOTHING_SELECTED;
						break;
				}

				//After action recalculate positions and occupied tiles
				updateOccupiedTiles();
				updateRanges();
				break;

			//Reset position
			case eBUTTON::CANCEL:
				getSelectedUnit()->resetPosition(m_map.getMapSize());
				m_actionMenu.hideActionMenu();
				m_sceneMode = eSCENE_MODE::PLAYER_TURN_SELECTED;
				break;

			default:
				break;
		}
	}
}

//Get selected unit
cUnit* cBattleScene::getSelectedUnit(){
	if(m_nSelectedUnit == -1){
		std::cout << "[ERROR] Call to selected unit when no unit is selected" << std::endl;
		return nullptr;
	}
	if(m_nSelectedUnit >= m_allyVector.size() or m_nSelectedUnit < -1){
		std::cout << "[ERROR] Selected unit does not exist" << std::endl;
		return nullptr;
	}
	return m_allyVector[m_nSelectedUnit].get();
}

//draw
void cBattleScene::draw(){
	//Draw map, pass camera offset
	m_map.draw(m_vCameraOffset);

	//Draw unit range only for selected unit and only in selected mode
	if(m_nSelectedUnit != -1)
		getSelectedUnit()->drawRange(m_nAnimationFrameCounter, m_vCameraOffset);

	//Draw units, pass animation frame and camera offset
	for(auto &UNIT : m_sortedUnitVector)
		UNIT->draw(m_nAnimationFrameCounter, m_vCameraOffset);
	

	//Draw cursor, pass animation frame and camera offset
	m_cursor.draw(m_nAnimationFrameCounter, m_vCameraOffset);

	//Draw action menu
	m_actionMenu.draw();
}
