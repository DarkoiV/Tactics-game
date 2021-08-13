#pragma once

// Animation interface
class cAnimation {
	public:
		// Destructor
		virtual ~cAnimation(){};

		// Draw animation
		virtual void draw() = 0;

		// is Completed
		virtual bool isCompleted() = 0;
};
