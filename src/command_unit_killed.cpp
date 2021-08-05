#include "command_unit_killed.hpp"

// Constructor
cCommandUnitKilled::cCommandUnitKilled(std::shared_ptr<cUnit> p_unit) {
	// Store unit
	m_unit = std::move(p_unit);

	std::cout << "[INFO] Unit killed" << std::endl;
}

// Draw information about death to screen
void cCommandUnitKilled::execute() {
	// TODO
	m_frameCounter++;
}

bool cCommandUnitKilled::isCompleted() {
	if(m_frameCounter == 60) 
		return true;
	else 
		return false;
}
