#pragma once

#include "struct_vec2D.hpp"

// Animation interface
class cAnimation {
	public:
		// Destructor
		virtual ~cAnimation(){};

		// Draw animation
		virtual void draw(vec2D p_cameraOffset) = 0;

		// is Completed
		virtual bool isCompleted() = 0;
};
