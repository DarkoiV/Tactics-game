#pragma once

#include "scene.hpp"

class cSceneBattle: public cScene{
	private:

	public:
		// Constructor/destructor
		cSceneBattle();
		~cSceneBattle();

		// Scene methods override
		void process(eBUTTON p_input) override;
		void update()                 override;
		void draw()                   override;
};
