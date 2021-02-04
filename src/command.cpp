#include "command.hpp"

//Move unit one tile in direction
void cCommandMove::execute(){
	//Move in right direction
	switch(m_DIRECTION){
		case eDIRECTION::NORTH:
			m_unit->movPosition({0, -m_vel});
			break;
		case eDIRECTION::SOUTH:
			m_unit->movPosition({0, m_vel});
			break;
		case eDIRECTION::EAST:
			m_unit->movPosition({m_vel, 0});
			break;
		case eDIRECTION::WEST:
			m_unit->movPosition({-m_vel, 0});
			break;
	}

	//Save moved ammount
	m_moved += m_vel;

	//If full tiled was moved, set completion flag, reset mov, and set pos
	if(m_moved == TILE_SIZE){
		m_completed = true;
		m_unit->finalizeMovement();
	}
}

//Return if move was completed
bool cCommandMove::isCompleted(){
	return m_completed;
}
