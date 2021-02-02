#include "battle_scene.hpp"

//constructor for editor
cBattleScene::cBattleScene(vec2D p_vMapSize) : m_map(p_vMapSize){
	//Set boundaries and starting position for cursor
	m_cursor.loadMapSize(p_vMapSize);
	m_cursor.setPosition({7, 7});

	//set unit position
	m_unit.setPosition({7, 7});

	//start in edit mode
	m_sceneMode = eSCENE_MODE::EDIT_MAP;
}

//constructor loading from file
cBattleScene::cBattleScene(std::string p_sMapName) : m_map(p_sMapName){
}

//Check command queue and handle commands
bool cBattleScene::checkCommandQueue(){
	if(not m_commandQueue.empty()){
		m_commandQueue.front()->execute();
		//if completed delete it from queue
		if(m_commandQueue.front()->isCompleted())
			m_commandQueue.pop();

		return true;
	}
	return false;
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
	//Check command queue, and disable input on command processing
	if(checkCommandQueue())
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
		case eSCENE_MODE::PLAYER_UNIT_MODE:
			updatePlayerUnitMode(p_INPUT);
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
		//On none, do nothing, lol
		case eBUTTON::NONE:
		default:
			 break;
	}

}

//Update player turn
void cBattleScene::updatePlayerTurn(eBUTTON p_INPUT){
}

//Update plyer unit mode
void cBattleScene::updatePlayerUnitMode(eBUTTON p_INPUT){
}

//draw
void cBattleScene::draw(){
	//Draw map, pass camera offset
	m_map.draw(m_vCameraOffset);

	//Draw units, pass animation frame and camera offset
	m_unit.draw(m_nAnimationFrameCounter, m_vCameraOffset);

	//Draw cursor, pass animation frame and camera offset
	m_cursor.draw(m_nAnimationFrameCounter, m_vCameraOffset);
}
