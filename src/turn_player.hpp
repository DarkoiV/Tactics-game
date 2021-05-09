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

	public:
		void start(cSceneBattle &scene)       override;
		bool isCompleted(cSceneBattle &scene) override;

		// Turn Loop
		void process(cSceneBattle &scene, 
			eBUTTON p_input)         override;
		void update(cSceneBattle &scene) override;
};
