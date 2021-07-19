#pragma once

#include "turn.hpp"
#include "command.hpp"
#include <memory>
#include <queue>

class cBoard;
class cCursor;
class cTeam;
class cQuickStats;

class cTurnPlayer: public cTurn{
	private:
		// Parent scene dependencies
		cBoard  	&board;
		cCursor 	&cursor;
		cQuickStats 	&qStats;
		cTeam   	&playerTeam;
		cTeam   	&enemyTeam;

		// Command queue
		std::queue<std::unique_ptr<cCommand>> m_commandQueue;

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
		cTurnPlayer(cBoard &b, cCursor &c, cQuickStats &qs, cTeam &pt, cTeam &et):
			board(b),
			cursor(c),
			qStats(qs),
			playerTeam(pt),
			enemyTeam(et){};

		void start()       override;
		bool isCompleted() override;

		// Turn Loop
		void update(eBUTTON p_input) override;
};
