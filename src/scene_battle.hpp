#pragma once

#include "scene.hpp"

class cSceneBattle: public cScene{
	private:

	public:
		// Constructor/destructor
		cSceneBattle();
		~cSceneBattle();

		// Scene methods override
		void processInput() override;
		void update()       override;
		void draw()         override;
};
