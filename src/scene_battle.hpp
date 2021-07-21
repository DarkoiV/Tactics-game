#pragma once

#include "scene.hpp"
#include "turn.hpp"
#include "turn_player.hpp"
#include "board.hpp"
#include "cursor.hpp"
#include "struct_vec2D.hpp"
#include "team.hpp"
#include "ui_quick_stats.hpp"
#include "commander.hpp"

#include <vector>
#include <memory>

class cSceneBattle: public cScene{
	private:
		// Scene components
		cBoard  	m_board;
		cCursor 	m_cursor;
		cQuickStats 	m_qStats;
		cCommander 	m_commander;

		// Teams
		cTeam m_blueTeam = cTeam(eTEAM_COLOR::BLUE);
		cTeam m_redTeam  = cTeam(eTEAM_COLOR::RED);

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
