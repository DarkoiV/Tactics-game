#pragma once

#include "enums.hpp"
#include <string>

// Scene interface
class cScene{
	public:
		// Destructor
		virtual ~cScene(){};

		// Parse console command
		virtual void command(const std::string& p_command) = 0;

		// Scene completed?
		virtual bool completed() =0;

		// Loop methods
		virtual void update(eBUTTON p_INPUT) = 0;
		virtual void draw()                  = 0;
};
