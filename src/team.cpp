#include "team.hpp"

// Add new unit to team by name
void cTeam::addNewUnit(std::string p_name){
	std::cout << "[INFO] Creating unit by name: " << p_name << std::endl;
	// Create TMP unit
	if(p_name == "TMP"){
		m_units.push_back(std::make_shared<cUnit>(p_name));
		m_units.back()->setPosition({10,10});
	}
}

// Try to select unit on target position, return true if any selectable unit is present on selected position
bool cTeam::selectUnit(vec2D p_targetPos){
	for(const auto &UNIT : m_units){
		if(UNIT->getPosition() == p_targetPos){
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
	}
	return *m_selectedUnit;
}

// Calculate range of units
void cTeam::calculateRange(cBoard &board, std::vector<bool> passableTiles){
	std::cout << "[INFO] Calculating units ranges" << std::endl;
	u_int32_t startTime = SDL_GetTicks(); 
	for(auto UNIT : m_units){
		UNIT->range().calculateRange(board, passableTiles);
	}
	std::cout << "[INFO] Calculating ranges took: "<< SDL_GetTicks() - startTime << "ms" << std::endl;
}

// Toggle move range drawing
void cTeam::toggleMoveRange(bool p_shown){
	m_showMoveRange = p_shown;
}

// Draw units
void cTeam::drawUnits(vec2D p_cameraOffset, int p_animationFrame){
	for(const auto &UNIT : m_units){
		UNIT->draw(p_cameraOffset, p_animationFrame);
	}
}

// Draw selected unit move range
void cTeam::drawMoveRange(vec2D p_cameraOffset, int p_animationFrame){
	if(m_selectedUnit != nullptr and m_showMoveRange)
		m_selectedUnit->range().drawMoveRange(p_cameraOffset, p_animationFrame);
	
}
