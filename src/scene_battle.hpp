#pragma once

#include "scene.hpp"
#include "board.hpp"
#include "struct_vec2D.hpp"

class cSceneBattle: public cScene{
	private:
		// Scene components
		cBoard m_board;

		// CAMERA
		vec2D m_cameraOffset{0, 0};

	public:
		// Constructor/destructor
		cSceneBattle();
		~cSceneBattle();

		// Scene methods override
		void process(eBUTTON p_input) override;
		void update()                 override;
		void draw()                   override;
};
