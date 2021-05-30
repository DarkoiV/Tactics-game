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
	const int boardLine = scene.board().getSize().x;
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
		and WEST >= 0
		and passableTiles[WEST]){
			m_validMoveDistance[WEST] = CURRENT_DISTANCE + 1;
			tilesToCheck.push(WEST);
		}

		tilesToCheck.pop();

	}

	for(auto const& [tile, distance] : m_validMoveDistance){
		vec2D tile2D = {tile % boardLine, tile / boardLine};
		m_validMove.push_back(tile2D);
	}
}

bool cUnitRange::canMove(cSceneBattle &scene, vec2D p_targetPos){
	// Calculate target tile in 1D space
	const int boardLine  = scene.board().getSize().x;
	const int targetTile = p_targetPos.x + (p_targetPos.y * boardLine);

	// Check if valid move
	if(m_validMoveDistance.count(targetTile) == 1)
		return true;
	else
		return false;
}

void cUnitRange::drawMoveRange(vec2D p_cameraOffset, int p_animationFrame){
	SDL_Rect srcRect{0, 0, TILE_SIZE, TILE_SIZE};
	SDL_Rect dstRect{0, 0, TILE_SIZE, TILE_SIZE};

	// Animation frame, 0 - 25 - first frame, 25 - 30 second frame etc...
	srcRect.x = (TILE_SIZE + TILE_SIZE * ((p_animationFrame - 25)/5)) * (p_animationFrame >= 25);

	//Draw range tiles to screen 
	for(size_t i = 0; i < m_validMove.size(); i++){
		dstRect.x = m_validMove[i].x * TILE_SIZE + p_cameraOffset.x;
		dstRect.y = m_validMove[i].y * TILE_SIZE + p_cameraOffset.y;
		SDL_RenderCopy(g_renderer, m_moveRangeSprite, &srcRect, &dstRect);
	}
}
