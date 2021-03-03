#include "command.hpp"

//////MOVE/////////////////////////////////////////////////////////////////////////////////////

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

//////ATTACK///////////////////////////////////////////////////////////////////////////////////

//Perform attack 
void cCommandAttack::execute(){
	//Unit move backs before attack
	if(m_nAttackFrame < 20 and m_nAttackFrame % 5 == 0){
		switch(m_DIRECTION){
			case eDIRECTION::NORTH:
				m_attackingUnit->movPosition({0, m_vel});
				break;
			case eDIRECTION::SOUTH:
				m_attackingUnit->movPosition({0, -m_vel});
				break;
			case eDIRECTION::EAST:
				m_attackingUnit->movPosition({-m_vel, 0});
				break;
			case eDIRECTION::WEST:
				m_attackingUnit->movPosition({m_vel, 0});
				break;
		}
	}
	//Unit attacks
	else if(m_nAttackFrame == 30){
		switch(m_DIRECTION){
			case eDIRECTION::NORTH:
				m_attackingUnit->movPosition({0, -m_vel * 5 });
				break;
			case eDIRECTION::SOUTH:
				m_attackingUnit->movPosition({0, m_vel * 5});
				break;
			case eDIRECTION::EAST:
				m_attackingUnit->movPosition({m_vel * 5, 0});
				break;
			case eDIRECTION::WEST:
				m_attackingUnit->movPosition({-m_vel * 5, 0});
				break;
		}
	}
	//Reset position
	else if(m_nAttackFrame == 35){
		switch (m_DIRECTION) {
			case eDIRECTION::NORTH:
				m_attackingUnit->movPosition({0, m_vel});
				break;
			case eDIRECTION::SOUTH:
				m_attackingUnit->movPosition({0, -m_vel});
				break;
			case eDIRECTION::EAST:
				m_attackingUnit->movPosition({-m_vel, 0});
				break;
			case eDIRECTION::WEST:
				m_attackingUnit->movPosition({m_vel, 0});
				break;
		}
		m_targetUnit->m_unitState = cUnit::eUNIT_STATE::TOOK_DAMAGE;
	}
	else if(m_nAttackFrame == 60){
		m_targetUnit->m_unitState = cUnit::eUNIT_STATE::IDLE;
		m_attackingUnit->setExhausted();
	}

	if(m_nAttackFrame == 61)
		m_completed = true;
	m_nAttackFrame++;
}

//Return if attack was completed
bool cCommandAttack::isCompleted(){
	return m_completed;
}
