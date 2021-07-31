#include "scene_battle.hpp"

#include <sstream>

// Constructor VERSUS MODE
cSceneBattle::cSceneBattle(){
	// Load board map
	m_board.load("TEST");

	// Init cursor
	m_cursor.init(m_board.getSize());
	
	// Create player turns
	// BLUE PLAYER
	m_turnVector.emplace_back( new cTurnPlayer (
		m_board,
		m_cursor,
		m_UI,
		m_commander,
		m_blueTeam,
		m_redTeam
		));
	// RED PLAYER
	m_turnVector.emplace_back( new cTurnPlayer (
		m_board,
		m_cursor,
		m_UI,
		m_commander,
		m_redTeam,
		m_blueTeam
		));

	// Register lua functions
	lua_register(m_lua(), "offsetUnit", cUnit::l_offsetUnit);

	// TMP create units
	m_blueTeam.spawnUnit("TMP", {8, 10});
	m_blueTeam.spawnUnit("TMP", {9, 10});

	// m_redTeam.addNewUnit("TMP");
	m_redTeam.spawnUnit("TMP", {5, 10});
	m_redTeam.spawnUnit("TMP", {4, 10});

	// Start current turn
	currentTurn()->start();
}

// Destructor
cSceneBattle::~cSceneBattle(){
	// Free memory
	std::cout << "[INFO] Deleting turns data" << std::endl;
	for(size_t i = 0; i < m_turnVector.size(); i++){
		delete m_turnVector[i];
	}
}

// Update camera position
inline void cSceneBattle::updateCamera(){
	// X axis
	const int cursorPosX = m_cursor.position().x * TILE_SIZE;
	m_cameraOffset.x 
		-= TILE_SIZE
		*  (m_cameraOffset.x + cursorPosX > SCREEN_WIDTH - TILE_SIZE);

	m_cameraOffset.x 
		+= TILE_SIZE
		*  ( (-m_cameraOffset.x) > cursorPosX);

	// Y axis
	const int cursorPosY = m_cursor.position().y * TILE_SIZE;
	m_cameraOffset.y
		-= TILE_SIZE
		*  (m_cameraOffset.y + cursorPosY > SCREEN_HEIGHT - TILE_SIZE);

	m_cameraOffset.y 
		+= TILE_SIZE
		*  ( (-m_cameraOffset.y) > cursorPosY);
}

// TURN METHODS ////////////////////////////////////////////////////////////

// Get current turn
auto cSceneBattle::currentTurn() -> cTurn*{
	return m_turnVector[m_turnIndex];
}

// Switch to next turn
void cSceneBattle::nextTurn(){
	std::cout << "[INFO] Starting new turn" << std::endl;

	m_turnIndex++;
	if((size_t)m_turnIndex >= m_turnVector.size())
		m_turnIndex = 0;

	currentTurn()->start();
}

// SCENE METHODS ///////////////////////////////////////////////////////////

// Parse console command 
void cSceneBattle::command(const std::string &p_command){
	std::cout << "[INFO] Issued command: "<< p_command << std::endl;

	// Split string into arguments
	std::vector<std::string> arguments;
	{
		std::string current_argument;
		std::stringstream commandStream(p_command);
		while(getline(commandStream, current_argument, ' '))
				arguments.push_back(current_argument);
	}

	if(arguments.size() < 1){
		std::cout << "[INFO] Empty command" << std::endl;
		return;
	}
	if(arguments[0] == "next_turn"){
		std::cout << "[INFO] Switching to next turn via command" << std::endl;
		nextTurn();
	}
}

// Update scene
void cSceneBattle::update(eBUTTON p_input){
	// Process turn related input
	currentTurn()->update(p_input);

	// Check turn status
	switch(currentTurn()->status()){
		// Do nothing
		case eTURN_STATUS::IN_PROGRESS:
			break;

		// Switch to next turn
		case eTURN_STATUS::COMPLETED:
			nextTurn();
			break;

		// Switch to next turn after deleting turn from vector
		case eTURN_STATUS::TO_BE_REMOVED:
			// TODO implement
			nextTurn();
			break;
	}

	// Update camera
	updateCamera();
}

// Draw scene
void cSceneBattle::draw(){
	// Animation frame
	static int animationFrame;
	animationFrame++;
	animationFrame = animationFrame % 60;

	// Draw board
	m_board.draw(m_cameraOffset);

	// Draw move ranges
	m_blueTeam.drawRange(m_cameraOffset, animationFrame);
	m_redTeam.drawRange(m_cameraOffset, animationFrame);

	// Draw units
	m_blueTeam.drawUnits(m_cameraOffset, animationFrame);
	m_redTeam.drawUnits(m_cameraOffset, animationFrame);

	// Draw cursor
	m_cursor.draw(m_cameraOffset, animationFrame);

	// Draw UI
	m_UI.qStats.draw();
	m_UI.aMenu.draw();
}
