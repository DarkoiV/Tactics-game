#pragma once

#include "enums.hpp"
#include "struct_vec2D.hpp"

enum class eTURN_STATUS{
	IN_PROGRESS,	// Called when turn is in progress
	COMPLETED,	// Called when turn was completed
	TO_BE_REMOVED	// Called when turn was completed, and should not be called again
};

// Turn component interface
class cTurn{
	public:
		// Destructor
		virtual ~cTurn(){};

		// Start turn
		virtual void start() = 0;

		// Check turn status
		virtual auto status() -> eTURN_STATUS = 0;

		// Turn Loop
		virtual void update(eBUTTON p_input) = 0;
};
