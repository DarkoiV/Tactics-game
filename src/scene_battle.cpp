#include "scene_battle.hpp"

// Constructor 
cSceneBattle::cSceneBattle(){
	// Load board map
	m_board.load("TEST");

	// Init cursor
	m_cursor.init(m_board.getSize());

	// Start player turn
	m_turnVector.push_back(&m_playerTurn);
	currentTurn()->start(*this);

	// TMP create unit
	m_unit.setPosition({7, 7});
	m_unit.range().calculateRange(m_unit, *this, m_board.getPassableForUnit());
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

// GAME LOOP METHODS ///////////////////////////////////////////////////////

// Process input
void cSceneBattle::process(eBUTTON p_input){
	// Process turn related input
	currentTurn()->process(*this, p_input);
}

// Update scene
void cSceneBattle::update(){
	// Update turn
	currentTurn()->update(*this);

	// Check if is completed, if so, switch to next turn
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

	// Draw components
	m_board.draw(m_cameraOffset);
	m_cursor.draw(m_cameraOffset, animationFrame);

	//TMP unit
	m_unit.range().drawMoveRange(m_cameraOffset, animationFrame);
	m_unit.draw(m_cameraOffset, animationFrame);
}

// GET COMPONENT METHODS ///////////////////////////////////////////////////

auto cSceneBattle::board() -> cBoard&{
	return m_board;
}

auto cSceneBattle::cursor() -> cCursor&{
	return m_cursor;
}
