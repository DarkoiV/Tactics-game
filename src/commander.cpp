#include "commander.hpp"

//Check if command queue is empty, if not process commands
bool cCommander::isProcessingCommands(){
	if( m_commandQueue.empty() )
		return false;

	//Execute first command in queue, if completed pop it from queue
	m_commandQueue.front()->execute();
	if(m_commandQueue.front()->isCompleted())
		m_commandQueue.pop();

	return true;
}

//Create and push new move command to queue
void cCommander::moveUnit(cUnit *p_unit, eDIRECTION p_DIRECTION){
	m_commandQueue.push(std::make_unique<cCommandMove>(p_unit, p_DIRECTION));
}

//Create and push new attack command to queue
void cCommander::attackUnit(cUnit *p_attackingUnit, cUnit *p_targetUnit){
	//Calculate direction off attack
	eDIRECTION directionOfAttack;
	int horizontal = p_attackingUnit->m_vPos.x - p_targetUnit->m_vPos.x;
	int vertical = p_attackingUnit->m_vPos.y - p_targetUnit->m_vPos.y;

	if(abs(horizontal) > abs(vertical)){
		if(horizontal > 0)
			directionOfAttack = eDIRECTION::WEST;
		else
			directionOfAttack = eDIRECTION::EAST;
	}
	else{
		if(vertical > 0)
			directionOfAttack = eDIRECTION::SOUTH;
		else
			directionOfAttack = eDIRECTION::NORTH;
	}

	m_commandQueue.push(std::make_unique<cCommandAttack>(p_attackingUnit, p_targetUnit, directionOfAttack));
}
