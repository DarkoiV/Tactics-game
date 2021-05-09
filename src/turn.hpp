#pragma once

#include "enums.hpp"
#include "struct_vec2D.hpp"

// Turn component interface
class cTurn{
	public:
		// Destructor
		virtual ~cTurn(){};

		// Methods
		virtual void start()       = 0;
		virtual bool isCompleted() = 0;

		// Turn Loop
		virtual void process(eBUTTON p_input)    = 0;
		virtual void update()                    = 0;
		virtual void draw(vec2D p_cameraOffsety) = 0;
};
