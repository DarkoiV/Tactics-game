#pragma once

#include "enums.hpp"
#include "struct_vec2D.hpp"

class cSceneBattle;

// Turn component interface
class cTurn{
	public:
		// Destructor
		virtual ~cTurn(){};

		// Methods
		virtual void start(cSceneBattle &scene)       = 0;
		virtual bool isCompleted(cSceneBattle &scene) = 0;

		// Turn Loop
		virtual void update(cSceneBattle &scene
			, eBUTTON p_input)               = 0;
};
