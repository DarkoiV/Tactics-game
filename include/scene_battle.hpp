#pragma once

#include "scene.hpp"
#include "turn.hpp"
#include "turn_player.hpp"
#include "board.hpp"
#include "cursor.hpp"
#include "struct_vec2D.hpp"
#include "team.hpp"
#include "ui_collection.hpp"
#include "commander.hpp"
#include "animator.hpp"
#include "battle_lua.hpp"

#include <vector>
#include <memory>

class cSceneBattle: public cScene{
	private:
		// Scene Lua
		cBattleLua	m_lua;	

		// Scene components
		cBoard  	m_board;
		cCursor 	m_cursor;
		cUI 		m_UI 		= cUI(m_lua);
		cAnimator	m_animator;
		cCommander 	m_commander 	= cCommander(m_lua, m_animator);

		// Teams
		cTeam m_blueTeam = cTeam(m_lua, eTEAM_COLOR::BLUE);
		cTeam m_redTeam  = cTeam(m_lua, eTEAM_COLOR::RED);

		// CAMERA
		vec2D m_cameraOffset{0, 0};
		inline void updateCamera();

		// Turn methods
		int  m_turnIndex    = 0;
		auto currentTurn() -> cTurn*;
		void nextTurn();

		// Turn components
		std::vector<cTurn*> m_turnVector;

	public:
		// Constructor/destructor
		cSceneBattle();
		~cSceneBattle();

		// Parse console command
		void command(const std::string& p_command) override;

		// Scene loop methods override
		void update(eBUTTON p_INPUT) override;
		void draw()                  override;
};
