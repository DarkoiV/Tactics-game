#pragma once

#include "turn.hpp"
#include "cursor.hpp"

class cTurnPlayer: public cTurn{
	private:
		// Components
		cCursor m_cursor;

	public:
		// Methods
		void init(vec2D p_boardSize);
		void start()       override;
		bool isCompleted() override;

		// Turn Loop
		void process(eBUTTON p_input)   override;
		void update()                   override;
		void draw(vec2D p_cameraOffset 
			, int p_animationFrame) override;
};
