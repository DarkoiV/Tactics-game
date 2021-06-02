#include "scene_battle.hpp"

// Constructor 
cSceneBattle::cSceneBattle(){
	// Load board map
	m_board.load("TEST");

	// Init cursor
	m_cursor.init(m_board.getSize());

	// TMP create unit
	m_playerTeam.addNewUnit("TMP");
	m_playerTeam.addNewUnit("TMP");
	m_playerTeam.addNewUnit("TMP");
	m_playerTeam.addNewUnit("TMP");
	m_playerTeam.addNewUnit("TMP");
	m_playerTeam.addNewUnit("TMP");
	m_playerTeam.addNewUnit("TMP");
	m_playerTeam.addNewUnit("TMP");
	m_playerTeam.addNewUnit("TMP");
	m_playerTeam.addNewUnit("TMP");
	m_playerTeam.addNewUnit("TMP");
	m_playerTeam.addNewUnit("TMP");
	m_playerTeam.addNewUnit("TMP");
	m_playerTeam.addNewUnit("TMP");
	m_playerTeam.addNewUnit("TMP");
	m_playerTeam.addNewUnit("TMP");
	m_playerTeam.addNewUnit("TMP");
	m_playerTeam.addNewUnit("TMP");
	m_playerTeam.addNewUnit("TMP");
	m_playerTeam.addNewUnit("TMP");
	m_playerTeam.addNewUnit("TMP");
	m_playerTeam.addNewUnit("TMP");
	m_playerTeam.addNewUnit("TMP");
	m_playerTeam.addNewUnit("TMP");
	m_playerTeam.addNewUnit("TMP");

	// Start player turn
	m_turnVector.push_back(&m_playerTurn);
	currentTurn()->start(*this);
}

// Destructor
cSceneBattle::~cSceneBattle(){

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
	return m_turnVector[0];
}

// Switch to next turn
void cSceneBattle::nextTurn(){
}

// SCENE METHODS ///////////////////////////////////////////////////////////

// Parse console command 
void cSceneBattle::command(const std::string &p_command){
	std::cout << "[INFO] Issued command: "<< p_command << std::endl;
}

// Update scene
void cSceneBattle::update(eBUTTON p_input){
	// Process turn related input
	currentTurn()->update(*this, p_input);

	// Check if turn is completed, if so, switch to next turn
	if(currentTurn()->isCompleted(*this)){
		nextTurn();
		currentTurn()->start(*this);
	}

	updateCamera();
}

// Draw scene
void cSceneBattle::draw(){
	// Animation frame
	static int animationFrame;
	animationFrame++;
	animationFrame = animationFrame % 60;

	// Draw everything in order
	m_board.draw(m_cameraOffset);
	m_playerTeam.drawMoveRange(m_cameraOffset, animationFrame);
	m_playerTeam.drawUnits(m_cameraOffset, animationFrame);
	m_cursor.draw(m_cameraOffset, animationFrame);
}

// ACCESS COMPONENT METHODS /////////////////////////////////////////////////

auto cSceneBattle::board() -> cBoard&{
	return m_board;
}

auto cSceneBattle::cursor() -> cCursor&{
	return m_cursor;
}

auto cSceneBattle::pTeam() -> cTeam&{
	return m_playerTeam;
}
