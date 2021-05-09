#pragma once

#include "turn.hpp"

class cTurnPlayer: public cTurn{
	private:

	public:
		void start(cSceneBattle &scene)       override;
		bool isCompleted(cSceneBattle &scene) override;

		// Turn Loop
		void process(cSceneBattle &scene, 
			eBUTTON p_input)         override;
		void update(cSceneBattle &scene) override;
};
