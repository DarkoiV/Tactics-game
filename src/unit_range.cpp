#include "unit_range.hpp"
#include "unit.hpp"
#include "board.hpp"
#include "asset_manager.hpp"
#include <queue>

// Constructor loads sprite and connects to parent unit
cUnitRange::cUnitRange(cUnit &u) : unit(u){
	// Get sprite pointer
	auto &assetAccess = cAssetManager::getInstance();
	m_moveRangeSprite = assetAccess.getSprite("Unit range component", "move_range");
}

// Calculate range on board
void cUnitRange::calculateRange(cBoard &board, std::vector<bool> passableTiles){
	// Set constants used for rangefinsing
	const int boardLine = board.getSize().x;
	const int positionTile = unit.m_pos.x + (unit.m_pos.y * boardLine);
	const int lastTile = board.getSize().x * boardLine - 1;
	const int moveRange = unit.m_stats.MOV;

	// Reset move range containers
	m_validMove.clear();
	m_validMoveDistance.clear();

	// BFS algorithm, create queue, push current position
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
		and passableTiles[NORTH]
		and not m_validMoveDistance.count(NORTH)){
			m_validMoveDistance[NORTH] = CURRENT_DISTANCE + 1;
			tilesToCheck.push(NORTH);
		}

		if( EAST / boardLine == tilesToCheck.front() / boardLine
		and passableTiles[EAST]
		and not m_validMoveDistance.count(EAST)){
			m_validMoveDistance[EAST] = CURRENT_DISTANCE + 1;
			tilesToCheck.push(EAST);
		}

		if( SOUTH <= lastTile
		and passableTiles[SOUTH]
		and not m_validMoveDistance.count(SOUTH)){
			m_validMoveDistance[SOUTH] = CURRENT_DISTANCE + 1;
			tilesToCheck.push(SOUTH);
		}

		if( WEST / boardLine == tilesToCheck.front() / boardLine
		and WEST >= 0
		and passableTiles[WEST]
		and not m_validMoveDistance.count(WEST)){
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

// Return true if targetPos is passable tile
bool cUnitRange::inRange(cBoard &board, vec2D p_targetPos){
	// Calculate target tile in 1D space
	const int boardLine  = board.getSize().x;
	const int targetTile = p_targetPos.x + p_targetPos.y * boardLine;

	// Check if valid move
	if(m_validMoveDistance.count(targetTile) == 1)
		return true;
	else
		return false;
}

// Get stack of path directions
auto cUnitRange::getPath(cBoard &board, vec2D p_targetPos) -> std::stack<eDIRECTION>{
	std::stack<eDIRECTION> pathStack;

	// Set constants
	const int boardLine = board.getSize().x;
	const int targetTile = (p_targetPos.y * boardLine) + p_targetPos.x;

	// Setup distance, and current tile
	int distance = 0;
	int currentTile = targetTile;
	if(m_validMoveDistance.count(targetTile))
		distance = m_validMoveDistance[targetTile];
	else
		std::cout << "[ERROR] Tile is not a valid movement target" << std::endl;

	std::cout << "[INFO] Distance in path: " << distance << std::endl;

	// Create path
	while(distance > 0){
		// Check if surrounding tiles have smaller distance
		const int NORTH = currentTile - boardLine;
		const int EAST  = currentTile + 1;
		const int SOUTH = currentTile + boardLine;
		const int WEST  = currentTile - 1;

		// NORTH
		if (m_validMoveDistance.count(NORTH) 
		and m_validMoveDistance[NORTH] < distance){
			currentTile = NORTH;
			distance = m_validMoveDistance[NORTH];
			
			// Push movement from new found tile to current
			pathStack.push(eDIRECTION::SOUTH);
		}

		// EAST
		else if (m_validMoveDistance.count(EAST) 
		and m_validMoveDistance[EAST] < distance){
			currentTile = EAST;
			distance = m_validMoveDistance[EAST];
			
			// Push movement from new found tile to current
			pathStack.push(eDIRECTION::WEST);	
		}

		// SOUTH
		else if (m_validMoveDistance.count(SOUTH) 
		and m_validMoveDistance[SOUTH] < distance){
			currentTile = SOUTH;
			distance = m_validMoveDistance[SOUTH];
			
			// Push movement from new found tile to current
			pathStack.push(eDIRECTION::NORTH);	
		}

		// WEST	
		else if (m_validMoveDistance.count(WEST) 
		and m_validMoveDistance[WEST] < distance){
			currentTile = WEST;
			distance = m_validMoveDistance[WEST];
			
			// Push movement from new found tile to current
			continue;
		}

		// If could not find path
		else {
			std::cout << "[ERROR] Could not find proper path, returning empty stack!" << std::endl;
			while(not pathStack.empty())
			     pathStack.pop();
			break;
		}

	}

	// Return path to target
	return pathStack;
}

// Draw move range
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
