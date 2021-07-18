#include "scene_battle.hpp"

// Constructor VERSUS MODE
cSceneBattle::cSceneBattle(){
	// Load board map
	m_board.load("TEST");

	// Init cursor
	m_cursor.init(m_board.getSize());
	
	// Create player turns
	m_turnVector.emplace_back( new cTurnPlayer (
		m_board,
		m_cursor,
		m_blueTeam
		));

	// Start current turn
	currentTurn()->start();

	// TMP create units
	m_blueTeam.addNewUnit("TMP");
	m_blueTeam.addNewUnit("TMP");

	m_redTeam.addNewUnit("TMP");
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
	m_turnIndex++;
	if((size_t)m_turnIndex >= m_turnVector.size())
		m_turnIndex = 0;
}

// SCENE METHODS ///////////////////////////////////////////////////////////

// Parse console command 
void cSceneBattle::command(const std::string &p_command){
	std::cout << "[INFO] Issued command: "<< p_command << std::endl;
}

// Update scene
void cSceneBattle::update(eBUTTON p_input){
	// Process turn related input
	currentTurn()->update(p_input);

	// Check if turn is completed, if so, switch to next turn
	if(currentTurn()->isCompleted()){
		nextTurn();
		currentTurn()->start();
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

	m_blueTeam.drawMoveRange(m_cameraOffset, animationFrame);
	m_blueTeam.drawUnits(m_cameraOffset, animationFrame);

	m_redTeam.drawMoveRange(m_cameraOffset, animationFrame);
	m_redTeam.drawUnits(m_cameraOffset, animationFrame);

	m_cursor.draw(m_cameraOffset, animationFrame);
}
