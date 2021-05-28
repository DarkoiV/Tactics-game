#pragma once

#include "turn.hpp"

class cTurnPlayer: public cTurn{
	private:
		// Turn Mode
		enum {
			SELECT_UNIT,
			MOVE_UNIT,
			SELECT_ACTION,
			SELECT_TARGET
		} m_mode;

		// SELECT UNIT MODE
		void processSelectUnit(cSceneBattle &scene, eBUTTON p_input);

		// MOVE UNIT MODE
		void processMoveUnit(cSceneBattle &scene, eBUTTON p_input);

		// SELECT ACTION MODE
		void processSelectAction(cSceneBattle &scene, eBUTTON p_input);

		// SELECT TARGET MODE
		void processSelectTarget(cSceneBattle &scene, eBUTTON p_input);

	public:
		void start(cSceneBattle &scene)       override;
		bool isCompleted(cSceneBattle &scene) override;

		// Turn Loop
		void process(cSceneBattle &scene, 
			eBUTTON p_input)         override;
		void update(cSceneBattle &scene) override;
};
