#include "unit_range.hpp"
#include "unit.hpp"
#include "scene_battle.hpp"
#include "asset_manager.hpp"

cUnitRange::cUnitRange(){
	// Get sprite pointer
	auto &assetAccess = cAssetManager::getInstance();
	m_moveRangeSprite = assetAccess.getSprite("Unit range component", "move_range");
}

void cUnitRange::calculateRange(cUnit &unit, cSceneBattle &scene){
	// Set constants used for rangefinsing
	const int boardLine = scene.board().getSize().y;
	const int positionTile = unit.m_pos.x + (unit.m_pos.y * boardLine);

	// Reset move range containers
	m_validMove.clear();
	m_validMoveDistance.clear();

	// TODO: Create BFS algorithm
}

bool cUnitRange::canMove(cSceneBattle &scene, vec2D p_targetPos){
	// Calculate target tile in 1D space
	const int boardLine  = scene.board().getSize().y;
	const int targetTile = p_targetPos.x + (p_targetPos.y * boardLine);

	// Check if valid move
	if(m_validMoveDistance.count(targetTile) == 1)
		return true;
	else
		return false;
}

void cUnitRange::drawMoveRange(cSceneBattle &scene){
	// TODO
}
