#pragma once

#include <sstream>
#include "scene.hpp"
#include "map.hpp"
#include "cursor.hpp"
#include "unit.hpp"
#include "commander.hpp"

class cBattleScene : public cScene{
	protected:
		//objects
		cCursor m_cursor;
		cMap m_map;
		cCommander m_commander;
		cUnit m_unit;

		//Unit containers
		std::vector<std::shared_ptr<cUnit>> m_allyVector;
		std::vector<std::shared_ptr<cUnit>> m_enemyVector;
		std::vector<std::shared_ptr<cUnit>> m_sortedUnitVector;

		//Scene modes
		enum class eSCENE_MODE{
			BATTLE_PREP,
			NEW_TURN,
			PLAYER_TURN,
			ENEMY_TURN,
			EDIT_MAP
		} m_sceneMode;

		int m_nAnimationFrameCounter = 0;			//Counter used for displaying animations

		//Updates for diffrent modes
		void updateEdit(eBUTTON p_INPUT);
		void updatePlayerTurn(eBUTTON p_INPUT);

//////////////////CAMERA////////////////////////////////////////////////////////////////////////////////////////////////////////
	protected:
		vec2D m_vCameraOffset = {0,0};				//Camera offset in pixels

		void updateCamera();
		enum class eCAMERA{					//Behaviour of camera
			CENTERED,
			EDGE_SCROLLING
		} m_cameraMode = eCAMERA::EDGE_SCROLLING;

//////////////////EDIT MODE/////////////////////////////////////////////////////////////////////////////////////////////////////
	protected:
		int m_nCopiedTileID = 0;
		
		void processConsoleCommand(std::string p_sCommand);	//Process text from console

		void addAllyUnit(std::string p_sUnitName);
		void addEnemyUnit(std::string p_sUnitName);


//////////////////PLAYER TURN//////////////////////////////////////////////////////////////////////////////////////////////////
	protected:
		enum class eTURN_MODE{
			NOTHING_SELECTED,
			UNIT_SELECTED,
			UNIT_MOVED
		} m_turnMode = eTURN_MODE::NOTHING_SELECTED;

		void nothingSelected(eBUTTON p_INPUT);				//Selecting unit on map
		void unitSelected(eBUTTON p_INPUT);				//Oder unit to move around
		void selectAction(eBUTTON p_INPUT);				//Select action after movement

		int m_nSelectedUnit = -1;					//ID of selected unit
		cUnit* getSelectedUnit();					//Return selected unit, or nullptr if (-1)


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	public:
		//constructor/destructor
		cBattleScene(vec2D p_vMapSize);
		cBattleScene(std::string p_sMapName);

		//Update/draw
		void update(eBUTTON p_INPUT) override;
		void draw() override;
};
