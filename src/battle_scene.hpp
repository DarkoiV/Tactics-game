#pragma once

#include <sstream>
#include <set>
#include "scene.hpp"
#include "map.hpp"
#include "cursor.hpp"
#include "unit.hpp"
#include "commander.hpp"
#include "action_menu.hpp"

class cBattleScene : public cScene{
	protected:
		//objects
		cCursor m_cursor;
		cMap m_map;
		cCommander m_commander;
		cActionMenu m_actionMenu;

		//Unit containers
		std::vector<std::shared_ptr<cUnit>> m_allyVector;
		std::vector<std::shared_ptr<cUnit>> m_enemyVector;
		std::vector<std::shared_ptr<cUnit>> m_sortedUnitVector;

		//Sets of occupied tiles 
		std::set<int> m_occupiedByAllySet;
		std::set<int> m_occupiedByEnemySet;

		void updateOccupiedTiles();
		void updateRanges();

		//Scene modes
		enum class eSCENE_MODE{
			BATTLE_PREP,
			NEW_TURN,
			PLAYER_TURN_NOTHING_SELECTED,
			PLAYER_TURN_SELECTED,
			PLAYER_TURN_ACTION,
			ENEMY_TURN,
			EDIT_MAP
		} m_sceneMode;

		int m_nAnimationFrameCounter = 0;			//Counter used for displaying animations
		int m_nTurnCounter = 0;					//Counter for which turn it is now

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
		void updateEdit(eBUTTON p_INPUT);			//Mode specific update

		int m_nCopiedTileID = 0;
		
		void processConsoleCommand(std::string p_sCommand);	//Process text from console

		void addAllyUnit(std::string p_sUnitName);
		void addEnemyUnit(std::string p_sUnitName);


//////////////////PLAYER TURN//////////////////////////////////////////////////////////////////////////////////////////////////
	protected:
		void startNewTurn();						//Start new turn
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
