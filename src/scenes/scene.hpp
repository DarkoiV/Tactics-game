#pragma once

// Scene interface
class cScene{
	public:
		// Destructor
		virtual ~cScene(){};

		// Methods
		virtual void processInput() = 0;
		virtual void update()       = 0;
		virtual void draw()         = 0;
};
