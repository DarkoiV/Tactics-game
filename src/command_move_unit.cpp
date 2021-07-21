#include "command_move_unit.hpp"
#include "globals.hpp"

// Move unit
void cCommandMove::execute(){
	switch (m_DIRECTION){
		case eDIRECTION::NORTH:
			m_unit->offsetPosition({0, -VELOCITY});
			m_traveled += VELOCITY;
			break;

		case eDIRECTION::EAST:
			m_unit->offsetPosition({VELOCITY, 0});
			m_traveled += VELOCITY;
			break;

		case eDIRECTION::SOUTH:
			m_unit->offsetPosition({0, VELOCITY});
			m_traveled += VELOCITY;
			break;

		case eDIRECTION::WEST:
			m_unit->offsetPosition({-VELOCITY, 0});
			m_traveled += VELOCITY;
			break;
	}

}

// Check if full tile was traveled
bool cCommandMove::isCompleted(){
	if(m_traveled == TILE_SIZE){
		// Load previous position
		vec2D newPos = m_unit->getPosition();

		// Change position
		switch (m_DIRECTION) {
			case eDIRECTION::NORTH:
				newPos.y--;
				break;

			case eDIRECTION::EAST:
				newPos.x++;
				break;

			case eDIRECTION::SOUTH:
				newPos.y++;
				break;

			case eDIRECTION::WEST:
				newPos.x--;
				break;
		} 
		m_unit->setPosition(newPos);

		// Reset offset
		m_unit->resetOffset();
		return true;
	}
	else
		return false;
}
