#include "unit_range.hpp"
#include "unit.hpp"
#include "scene_battle.hpp"
#include "asset_manager.hpp"
#include <queue>

cUnitRange::cUnitRange(){
	// Get sprite pointer
	auto &assetAccess = cAssetManager::getInstance();
	m_moveRangeSprite = assetAccess.getSprite("Unit range component", "move_range");
}

void cUnitRange::calculateRange(cUnit &unit, cSceneBattle &scene, const std::vector<bool> &passableTiles){
	// Set constants used for rangefinsing
	const int boardLine = scene.board().getSize().y;
	const int positionTile = unit.m_pos.x + (unit.m_pos.y * boardLine);
	const int lastTile = scene.board().getSize().x * boardLine - 1;
	const int moveRange = unit.m_stats.MOV;

	// Reset move range containers
	m_validMove.clear();
	m_validMoveDistance.clear();

	//BFS algorithm, create queue, push current position
	std::queue<int> tilesToCheck;
	tilesToCheck.push(positionTile);
	m_validMoveDistance[positionTile] = 0;

	// Search through tiles
	while(not tilesToCheck.empty()){
		const int CURRENT_DISTANCE = m_validMoveDistance[tilesToCheck.front()];
		if(CURRENT_DISTANCE == moveRange){
			tilesToCheck.pop();
			continue;
		}

		const int NORTH = tilesToCheck.front() - boardLine;
		const int EAST  = tilesToCheck.front() + 1;
		const int SOUTH = tilesToCheck.front() + boardLine;
		const int WEST  = tilesToCheck.front() - 1;

		if( NORTH > 0 
		and passableTiles[NORTH]){
			m_validMoveDistance[NORTH] = CURRENT_DISTANCE + 1;
			tilesToCheck.push(NORTH);
		}

		if( EAST / boardLine == tilesToCheck.front() / boardLine
		and passableTiles[EAST]){
			m_validMoveDistance[EAST] = CURRENT_DISTANCE + 1;
			tilesToCheck.push(EAST);
		}

		if( SOUTH <= lastTile
		and passableTiles[SOUTH]){
			m_validMoveDistance[SOUTH] = CURRENT_DISTANCE + 1;
			tilesToCheck.push(SOUTH);
		}

		if( WEST / boardLine == tilesToCheck.front() / boardLine
		and passableTiles[WEST]){
			m_validMoveDistance[WEST] = CURRENT_DISTANCE + 1;
			tilesToCheck.push(WEST);
		}

		tilesToCheck.pop();

	}

	for(auto const& [tile, distance] : m_validMoveDistance){
		m_validMove.push_back(tile);
	}
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
	SDL_Rect srcRect;
	SDL_Rect dstRect;
}
