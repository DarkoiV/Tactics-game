#pragma once

#include "globals.hpp"

class cScene{
	public:
		//Constructor/destructor
		cScene(){};
		virtual ~cScene(){};

		//Methods
		virtual void update(eBUTTON p_INPUT) = 0;
		virtual void draw() = 0;
};
