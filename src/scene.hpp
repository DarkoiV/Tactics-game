#pragma once

#include "enums.hpp"

// Scene interface
class cScene{
	public:
		// Destructor
		virtual ~cScene(){};

		// Methods
		virtual void process(eBUTTON p_input) = 0;
		virtual void update()                 = 0;
		virtual void draw()                   = 0;
};
