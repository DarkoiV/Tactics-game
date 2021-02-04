#include "commander.hpp"

//Check if command queue is empty, if not process commands
bool cCommander::isProcessingCommands(){
	if( m_commandQueue.empty() )
		return false;

	return true;
}

void cCommander::moveUnit(cUnit *p_unit, eDIRECTION p_DIRECTION){
	m_commandQueue.push(std::unique_ptr<cCommand> (new cCommandMove(p_unit, p_DIRECTION)));
}
