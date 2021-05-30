#pragma once

#include "scene.hpp"
#include "turn.hpp"
#include "turn_player.hpp"
#include "board.hpp"
#include "cursor.hpp"
#include "struct_vec2D.hpp"
#include "team.hpp"
#include <vector>

class cSceneBattle: public cScene{
	private:
		// Scene components
		cBoard  m_board;
		cCursor m_cursor;

		// Teams
		cTeam m_playerTeam;

		// CAMERA
		vec2D m_cameraOffset{0, 0};
		inline void updateCamera();

		// Turn methods
		auto currentTurn() -> cTurn*;
		void nextTurn();

		// Turn components
		cTurnPlayer         m_playerTurn;
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

		// Access to components
		auto board()  -> cBoard&;
		auto cursor() -> cCursor&;
		auto pTeam()  -> cTeam&;
};
