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

	// ~ LUA ~
	cUnit::registerUnitApi(m_lua());

	// TMP create units
	m_blueTeam.spawnUnit("INFANTRY", {8, 10});
	m_blueTeam.spawnUnit("INFANTRY", {9, 10});
	m_blueTeam.spawnUnit("ARCHER", {10, 10});

	// m_redTeam.addNewUnit("TMP");
	m_redTeam.spawnUnit("INFANTRY", {5, 10});
	m_redTeam.spawnUnit("INFANTRY", {4, 10});
	m_redTeam.spawnUnit("ARCHER", {3, 10});

	// Start current turn
	currentTurn()->start();
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
	return m_turnVector[m_turnIndex].get();
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
		while(getline(commandStream, current_argument, ' ')){
			for( auto& c : current_argument ) c = toupper(c);
			arguments.push_back(current_argument);
		}
	}

	if(arguments.size() < 1) {
		std::cout << "[INFO] Empty command" << std::endl;
		return;
	}

	if(arguments[0] == "NEXTTURN") {
		std::cout << "[INFO] Switching to next turn via command" << std::endl;
		nextTurn();
	}

	// Commands after that requires at least 2 args
	if(arguments.size() < 2) {
		std::cout << "[WARN] Unknown command" << std::endl;
		return;
	}

	if(arguments[0] == "HEAL") {
		m_animator.animateEffect(m_cursor.position(), cAnimationEffect::eTYPE::HEAL);
		int amount = atoi(arguments[1].c_str());
		cUnit* unit;
		if(m_blueTeam.isAnyHere(m_cursor.position(), &unit)) unit->heal(amount);
		if(m_redTeam.isAnyHere(m_cursor.position(), &unit)) unit->heal(amount);
		return;
	}

	// Commands after that requires at least 3 args
	if(arguments.size() < 3) {
		std::cout << "[WARN] Unknown command" << std::endl;
		return;
	}

	// Spawn unit commands
	if(arguments[0] == "SPAWN") {
		if(arguments[1] == "BLUE" ) {
			m_blueTeam.spawnUnit(arguments[2], m_cursor.position());
			return;
		}

		if(arguments[1] == "RED" ) {
			m_redTeam.spawnUnit(arguments[2], m_cursor.position());
			return;
		}
	}

	std::cout << "[WARN] Unknown command" << std::endl;
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

	// Draw animations
	m_animator.draw(m_cameraOffset);

	// Draw UI
	m_UI.qStats.draw();
	m_UI.aMenu.draw();
}
