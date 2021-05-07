#pragma once

#include "enums.hpp"

// Turn component interface
class cTurn{
	public:
		// Destructor
		virtual ~cTurn();

		// Methods
		virtual void start();
		virtual bool isCompleted();

		// Turn Loop
		virtual void process(eBUTTON p_input);
		virtual void update();
		virtual void draw();
};
