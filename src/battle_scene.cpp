#include "battle_scene.hpp"

//constructor for editor
cBattleScene::cBattleScene(vec2D p_vMapSize) : m_map(p_vMapSize){
	//Set boundaries and starting position for cursor
	m_cursor.loadMapSize(p_vMapSize);
	m_cursor.setPosition({7, 7});

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
	updateEdit(p_INPUT);

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
			m_map.getTile(m_cursor.getPosition()).typeID++;
			std::cout << "[INFO] Tile at " << m_cursor.getPosition() << " changed(+1)" << std::endl;
			break;
		//On cancel, select previous tile
		case eBUTTON::CANCEL:
			m_map.getTile(m_cursor.getPosition()).typeID--;
			std::cout << "[INFO] Tile at " << m_cursor.getPosition() << " changed(-1)" << std::endl;
			break;
		//On special 1, copy
		case eBUTTON::SPECIAL:
			m_nCopiedTileID = m_map.getTile(m_cursor.getPosition()).typeID;
			std::cout << "[INFO] Copied tile type: " <<  m_map.getTile(m_cursor.getPosition()).typeID << std::endl;
			break;
		//On special 2, paste
		case eBUTTON::SPECIAL2:
			m_map.getTile(m_cursor.getPosition()).typeID = m_nCopiedTileID;
			std::cout <<"[INFO] Pasted tile type: " <<  m_map.getTile(m_cursor.getPosition()).typeID
				<< " at: " << m_cursor.getPosition() << std::endl;
			break;
		//On none, do nothing, lol
		case eBUTTON::NONE:
		default:
			 break;
	}

}

//draw
void cBattleScene::draw(){
	//Draw map, pass camera offset
	m_map.draw(m_vCameraOffset);

	//Draw cursor, pass animation frame and camera offset
	m_cursor.draw(m_nAnimationFrameCounter, m_vCameraOffset);
}
