#pragma once

#include "turn.hpp"

class cBoard;
class cCursor;
class cTeam;
class cQuickStats;
class cCommander;

class cTurnPlayer: public cTurn{
	private:
		// Parent scene dependencies
		cBoard  	&board;
		cCursor 	&cursor;
		cQuickStats 	&qStats;
		cCommander	&commander;
		cTeam   	&playerTeam;
		cTeam   	&enemyTeam;


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
		cTurnPlayer(cBoard &b, cCursor &c, cQuickStats &qs, cCommander &com, cTeam &pt, cTeam &et):
			board(b),
			cursor(c),
			qStats(qs),
			commander(com),
			playerTeam(pt),
			enemyTeam(et){};

		void start()       override;
		bool isCompleted() override;

		// Turn Loop
		void update(eBUTTON p_input) override;
};
