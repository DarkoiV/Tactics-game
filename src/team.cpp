#include "team.hpp"
#include "board.hpp"

// Spawn new unit, add it to team, by name
void cTeam::spawnUnit(const std::string &p_name, vec2D p_pos) {
	std::cout << "[INFO] Creating unit by name: " << p_name << std::endl;
	try {
		m_units.emplace_back(std::make_unique<cUnit>(p_name, m_teamColor, Lua));
		m_units.back()->setPosition(p_pos);
	} 
	catch(std::invalid_argument const &ex) {
		std::cout << "[WARN] Unit not spawned, " << ex.what() << std::endl;
	}
}

// Check if any unit is dead, reaturns how many
int cTeam::checkDeadUnits() {
	int deadUnits = 0;

	for(size_t i = 0; i < m_units.size(); i++) {
		if(m_units[i]->getStats().HP == 0) {
			m_units.erase(m_units.begin() + i);
			deadUnits++;
			i--;
		}
	}

	return deadUnits;
}

// Check if any unit is still active
bool cTeam::checkForActive() {
	for(size_t i = 0; i < m_units.size(); i++) {
		if(m_units[i]->isActive()) return true;
	}
	return false;
}


// Check if any unit remains alive
bool cTeam::alive() {
	return m_units.size() > 0;
}

// Try to select unit on target position, return true if any selectable unit is present on target position
bool cTeam::selectUnit(vec2D p_targetPos){
	for(const auto &UNIT : m_units){
		if(UNIT->isActive() and UNIT->getPosition() == p_targetPos){
			m_selectedUnit = UNIT.get();
			std::cout << "[INFO] Unit selected" << std::endl;
			return true;
			break;
		}
	}

	return false;
}

// Deselect unit
void cTeam::deselectUnit(){
	m_selectedUnit = nullptr;
}

// Get selected unit
auto cTeam::selected() -> cUnit&{
	if(m_selectedUnit == nullptr){
		std::cout << "[ERROR] Call to selected unit, when no unit selected" << std::endl;
		std::terminate();
	}
	return *m_selectedUnit;
}

// Calculate range of units
void cTeam::calculateRange(cBoard &board, cTeam &opposingTeam){
	std::cout << "[INFO] Calculating units ranges" << std::endl;
	u_int32_t startTime = SDL_GetTicks(); 

	auto passableTiles = board.getPassable(opposingTeam);

	for(auto &UNIT : m_units){
		UNIT->range().calculateRange(board, passableTiles);
	}
	std::cout << "[INFO] Calculating ranges took: "<< SDL_GetTicks() - startTime << "ms" << std::endl;
}

// Get occupied tiles by team
auto cTeam::getOccupiedTiles() -> std::vector<vec2D>{
	// Create return vector
	std::vector<vec2D> occupiedTiles(m_units.size());

	// Populate vector with positions occupied by team
	for(size_t i = 0; i < occupiedTiles.size(); i++){
		occupiedTiles[i] = m_units[i]->getPosition();
	}

	// Return
	return occupiedTiles;
}

// Check if there is any unit on target pos
bool cTeam::isAnyHere(vec2D p_targetPos, cUnit** unitHere){
	// Check if any is here
	for(size_t i = 0; i < m_units.size(); i++){
		if(p_targetPos == m_units[i]->getPosition()){
			if(unitHere != nullptr) *unitHere = m_units[i].get();
			return true;
		}
	}

	// If none is found return false
	return false;
}

// Toggle move range drawing
void cTeam::toggleMoveRange(bool p_shown){
	m_showMoveRange = p_shown;
}

// Toggle action range drawing
void cTeam::toggleActionRange(bool p_shown){
	m_showActionRange = p_shown;
}

// Reset active status
void cTeam::resetActiveStatus() {
	for(auto &UNIT : m_units)
		UNIT->toggleActive(true);
}

// Draw units
void cTeam::drawUnits(vec2D p_cameraOffset, int p_animationFrame){
	for(const auto &UNIT : m_units){
		UNIT->draw(p_cameraOffset, p_animationFrame);
	}
}

// Draw ranges
void cTeam::drawRange(vec2D p_cameraOffset, int p_animationFrame){
	if(m_selectedUnit != nullptr and m_showMoveRange)
		m_selectedUnit->range().drawMoveRange(p_cameraOffset, p_animationFrame);

	if(m_selectedUnit != nullptr and m_showActionRange)
		m_selectedUnit->range().drawActionRange(p_cameraOffset, p_animationFrame);	
}
