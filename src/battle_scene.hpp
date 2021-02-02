#pragma once

#include <queue>
#include <memory>

#include "scene.hpp"
#include "map.hpp"
#include "cursor.hpp"
#include "unit.hpp"
#include "command.hpp"

class cBattleScene : public cScene{
	protected:
		//objects
		cCursor m_cursor;
		cMap m_map;
		cUnit m_unit;

		//Command handling
		bool checkCommandQueue();				//Returns true if commands are being processed
		std::queue<std::unique_ptr<cCommand>> m_commandQueue;

		//variables
		vec2D m_vCameraOffset = {0,0};				//Camera offset in pixels

		enum class eSCENE_MODE{
			BATTLE_PREP,
			NEW_TURN,
			PLAYER_TURN,
			PLAYER_UNIT_MODE,
			ENEMY_TURN,
			EDIT_MAP
		} m_sceneMode;

		int m_nAnimationFrameCounter = 0;

		//Update for diffrent modes
		void updateEdit(eBUTTON p_INPUT);
		void updatePlayerTurn(eBUTTON p_INPUT);
		void updatePlayerUnitMode(eBUTTON p_INPUT);

		//Camera functions
		void updateCamera();
		enum class eCAMERA{					//Behaviour of camera
			CENTERED,
			EDGE_SCROLLING
		} m_cameraMode = eCAMERA::EDGE_SCROLLING;

		//Edit mode variables
		int m_nCopiedTileID = 0;


	public:
		//constructor/destructor
		cBattleScene(vec2D p_vMapSize);
		cBattleScene(std::string p_sMapName);

		//Update/draw
		void update(eBUTTON p_INPUT) override;
		void draw() override;
};
