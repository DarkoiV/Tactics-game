#include "unit_command_move.hpp"
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
	if(m_traveled == TILE_SIZE)
		return true;
	else
		return false;
}
