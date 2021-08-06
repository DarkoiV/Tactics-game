#pragma once

#include "turn.hpp"

class cBoard;
class cCursor;
class cTeam;
class cUI;
class cCommander;

class cTurnPlayer: public cTurn{
	private:
		// Parent scene dependencies
		cBoard  	&board;
		cCursor 	&cursor;
		cUI 		&UI;
		cCommander	&commander;
		cTeam   	&playerTeam;
		cTeam   	&enemyTeam;


		// Turn Mode
		enum {
			SELECT_UNIT,
			MOVE_UNIT,
			SELECT_ACTION,
			SELECT_TARGET,
			POST_ACTION
		} m_mode;

		// Turn status
		eTURN_STATUS m_status = eTURN_STATUS::IN_PROGRESS;

		void processSelectUnit(eBUTTON p_input);		// SELECT UNIT MODE
		void processMoveUnit(eBUTTON p_input);			// MOVE UNIT MODE
		void processSelectAction(eBUTTON p_input);		// SELECT ACTION MODE
		void processSelectTarget(eBUTTON p_input);		// SELECT TARGET MODE
		void processPostAction();				// POST ACTION CHECKUP

	public:
		cTurnPlayer(cBoard &b, cCursor &c, cUI &UI, cCommander &com, cTeam &pt, cTeam &et):
			board(b),
			cursor(c),
			UI(UI),
			commander(com),
			playerTeam(pt),
			enemyTeam(et){};

		// Override turn functions
		void start()       		override;
		auto status() -> eTURN_STATUS 	override;

		// Turn Loop
		void update(eBUTTON p_input) override;
};
