#include "commander.hpp"
#include "command_move_unit.hpp"
#include "command_attack_unit.hpp"
#include "command_unit_killed.hpp"

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

// Push attack command to queue
void cCommander::attack(cUnit *p_attacking, cUnit *p_target) {
	m_commandQueue.emplace(std::make_unique<cCommandAttack>(
		p_attacking,
		p_target,
		Lua
	));
}

// Push unit killed command to queue
void cCommander::unitKilled(const std::shared_ptr<cUnit> &p_unit) {
	m_commandQueue.emplace(std::make_unique<cCommandUnitKilled>(
		p_unit
	));
	animator.unitDied("INFANTRY");
}
