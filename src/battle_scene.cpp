#include "battle_scene.hpp"

//constructor for editor
cBattleScene::cBattleScene(vec2D p_vMapSize) : m_map(p_vMapSize){
	//Set boundaries and starting position for cursor
	m_cursor.loadMapSize(p_vMapSize);
	m_cursor.setPosition({7, 7});

	//Create and set unit position
	m_unitVector.emplace_back(std::make_shared<cUnit>());
	m_unitVector[0].get()->setPosition({7 , 7});

	//start in edit mode
	m_sceneMode = eSCENE_MODE::EDIT_MAP;
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

//Update
void cBattleScene::update(eBUTTON p_INPUT){
	//TMP calculateRange
	m_unitVector[0]->calculateRange(m_map.refMap(), m_map.getMapSize());

	//Check if commands are processed, if so disable inputs
	if(m_commander.isProcessingCommands())
		p_INPUT = eBUTTON::NONE;
	
	//Call mode specific update method
	switch(m_sceneMode){
		default:
		case eSCENE_MODE::EDIT_MAP:
			updateEdit(p_INPUT);
			break;
		case eSCENE_MODE::PLAYER_TURN:
			updatePlayerTurn(p_INPUT);
			break;
	}

	//Update camera
	updateCamera();

	//Update animation frame counter
	m_nAnimationFrameCounter++;
	if(m_nAnimationFrameCounter == 60)
		m_nAnimationFrameCounter = 0;
}

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
			m_sceneMode = eSCENE_MODE::PLAYER_TURN;
			break;
		//On none(or not used input here), do nothing, lol
		case eBUTTON::NONE:
		default:
			 break;
	}

	//Update all tiles mov cost
	m_map.setTilesMovCost();
}

//Update player turn
void cBattleScene::updatePlayerTurn(eBUTTON p_INPUT){
	//Move cursor, or open menu, other input processed in turn specific mode
	switch (p_INPUT) {
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
		//TMP switch modes, later open menu
		case eBUTTON::ESCAPE:
			m_sceneMode = eSCENE_MODE::EDIT_MAP;
			break;
		default:
			break;
	}

	//Behaviour based on turn state
	switch(m_turnMode){
		case eTURN_MODE::NOTHING_SELECTED:
			nothingSelected(p_INPUT);
			break;
		case eTURN_MODE::UNIT_SELECTED:
			unitSelected(p_INPUT);
			break;
		case eTURN_MODE::UNIT_MOVED:
			selectAction(p_INPUT);
			break;
	}
}

//Behaviour when no unit was selected
void cBattleScene::nothingSelected(eBUTTON p_INPUT){
	switch(p_INPUT){
		case eBUTTON::SELECT:
			//Check if there is unit under cursor
			if(m_unitVector[0]->isHere(m_cursor.getPosition())){
				//If there is, set which one and change mode to unit selected
				std::cout << "[INFO] Selected unit" << std::endl;
				m_nSelectedUnit = 0;
				m_turnMode = eTURN_MODE::UNIT_SELECTED;
			}
			break;
		case eBUTTON::NONE:
		default:
			break;
	}

}

//Move selected unit
void cBattleScene::unitSelected(eBUTTON p_INPUT){
	switch(p_INPUT){
		case eBUTTON::SELECT:
			//Check if move is withing range, if so move unit
			if (getSelectedUnit()->isMoveInRange(m_cursor.highlightedTile())){
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
				m_turnMode = eTURN_MODE::UNIT_MOVED;
			}
			break;
		case eBUTTON::CANCEL:
			//Deselect unit
			std::cout << "[INFO] Unit deselected" << std::endl;
			m_nSelectedUnit = -1;
			m_turnMode = eTURN_MODE::NOTHING_SELECTED;
			break;
		case eBUTTON::NONE:
		default:
			break;
	}
}

//Get selected unit
cUnit* cBattleScene::getSelectedUnit(){
	if(m_nSelectedUnit == -1){
		std::cout << "[ERROR] Call to selected unit when no unit is selected" << std::endl;
		return nullptr;
	}
	if(m_nSelectedUnit >= m_unitVector.size()){
		std::cout << "[ERROR] Selected unit does not exist" << std::endl;
		return nullptr;
	}
	return m_unitVector[m_nSelectedUnit].get();
}

//Select action to perform after move
void cBattleScene::selectAction(eBUTTON p_INPUT){
	//TMP switch to selection
	m_turnMode = eTURN_MODE::NOTHING_SELECTED;
	m_nSelectedUnit = -1;
}

//draw
void cBattleScene::draw(){
	//Draw map, pass camera offset
	m_map.draw(m_vCameraOffset);

	//Draw unit range only for selected unit
	if(m_nSelectedUnit != -1)
		getSelectedUnit()->drawRange(m_nAnimationFrameCounter, m_vCameraOffset);

	//Draw units, pass animation frame and camera offset
	m_unitVector[0]->draw(m_nAnimationFrameCounter, m_vCameraOffset);

	//Draw cursor, pass animation frame and camera offset
	m_cursor.draw(m_nAnimationFrameCounter, m_vCameraOffset);
}
