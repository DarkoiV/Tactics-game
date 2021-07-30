#include "commander.hpp"
#include "command_move_unit.hpp"
#include "command_attack_unit.hpp"

// Execute command from queue
bool cCommander::execute() {
	if( not m_commandQueue.empty() ){
		// Execute command
		m_commandQueue.front()->execute();

		// Check if command has finished
		if(m_commandQueue.front()->isCompleted())
			m_commandQueue.pop();

		// Return that commander is working
		return true;
	}
	else return false;
}

// Create queue of move command from path stack
void cCommander::moveUnit(cUnit *p_movedUnit, std::stack<eDIRECTION> p_directions) {
	while( not p_directions.empty() ){
		// Create move command
		m_commandQueue.emplace(std::make_unique<cCommandMove>(
			p_movedUnit,
			p_directions.top()
		));
		// Pop direction
		p_directions.pop();
	}
}

// Push attack command on queue
void cCommander::attack(cUnit *p_attacking, cUnit *p_target, const std::string &p_weapon){
	m_commandQueue.emplace(std::make_unique<cCommandAttack>(
		p_attacking,
		p_target,
		Lua,
		p_weapon
	));
}
