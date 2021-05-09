#pragma once

#include "scene.hpp"
#include "turn.hpp"
#include "turn_player.hpp"
#include "board.hpp"
#include "struct_vec2D.hpp"
#include <vector>

class cSceneBattle: public cScene{
	private:
		// Scene components
		cBoard  m_board;
		cCursor m_cursor;

		// CAMERA
		vec2D m_cameraOffset{0, 0};

		// Turn methods
		auto currentTurn() -> cTurn*;
		void nextTurn();

		// Turn objects and container
		cTurnPlayer         m_playerTurn;
		std::vector<cTurn*> m_turnVector;

	public:
		// Constructor/destructor
		cSceneBattle();
		~cSceneBattle();

		// Scene methods override
		void process(eBUTTON p_input) override;
		void update()                 override;
		void draw()                   override;

		// Get access components
		auto board()  -> cBoard&;
		auto cursor() -> cCursor&;
};
