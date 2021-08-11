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

// Push attack command to queue
void cCommander::attack(cUnit *p_attacking, cUnit *p_target) {
	m_commandQueue.emplace(std::make_unique<cCommandAttack>(
		p_attacking,
		p_target,
		Lua
	));
}

// Display text about killed units 
void cCommander::unitsKilled(int p_howMany, bool p_enemy) {
	std::string infoText;

	if (p_howMany == 1) {
		if(p_enemy) infoText = "ENEMY UNIT HAVE BEEN KILLED";
		else        infoText = "ALLY UNIT HAS DIED";
	}
	else {
		infoText = std::to_string(p_howMany);
		if(p_enemy) infoText += " ENEMY UNIS HAVE BEEN KILLED";
		else        infoText += " ALLY UNITS HAVE DIED";
	}

	animator.animateText(infoText, eTEXT_COLOR::RED, 3);
}
