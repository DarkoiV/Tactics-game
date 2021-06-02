#pragma once

#include "turn.hpp"

class cBoard;
class cCursor;
class cTeam;

class cTurnPlayer: public cTurn{
	private:
		// Parent scene dependencies
		cBoard  &board;
		cCursor &cursor;
		cTeam   &playerTeam;

		// Turn Mode
		enum {
			SELECT_UNIT,
			MOVE_UNIT,
			SELECT_ACTION,
			SELECT_TARGET
		} m_mode;

		// SELECT UNIT MODE
		void processSelectUnit(eBUTTON p_input);

		// MOVE UNIT MODE
		void processMoveUnit(eBUTTON p_input);

		// SELECT ACTION MODE
		void processSelectAction(eBUTTON p_input);

		// SELECT TARGET MODE
		void processSelectTarget(eBUTTON p_input);

	public:
		cTurnPlayer(cBoard &b, cCursor &c, cTeam &pt):
			board(b),
			cursor(c),
			playerTeam(pt){};

		void start()       override;
		bool isCompleted() override;

		// Turn Loop
		void update(eBUTTON p_input) override;
};
