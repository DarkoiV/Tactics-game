#pragma once

#include "enums.hpp"

// Scene interface
class cScene{
	public:
		// Destructor
		virtual ~cScene(){};

		// Methods
		virtual void update(eBUTTON p_INPUT) = 0;
		virtual void draw()                  = 0;
};
