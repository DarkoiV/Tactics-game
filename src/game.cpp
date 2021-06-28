#include "game.hpp"

#include "globals.hpp"
#include "asset_manager.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

// Constructor inits game
cGame::cGame(){
	// Load base path
	g_basePath = SDL_GetBasePath();
	std::cout << "[INFO] Game running in directory: " << g_basePath << std::endl;

	// Load config

	// Init SDL2
	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		std::cout << "[ERROR] SDL Init failed, " << SDL_GetError() << std::endl;
		return;
	}
	std::cout << "[OK] SDL Initialized" << std::endl;

	// Create window
	g_window = SDL_CreateWindow(g_title.c_str(), 
			SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, 
			SCREEN_WIDTH  * g_scaleFactor,
			SCREEN_HEIGHT * g_scaleFactor, 
			0);
	if(g_window == nullptr){
		std::cout << "[ERROR] SDL Window not created, " << SDL_GetError() << std::endl;
		return;
	}
	std::cout << "[OK] SDL Window created" << std::endl;

	// Create renderer
	g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
	if(g_renderer == nullptr){
		std::cout << "[ERROR] SDL Renderer not created, " << SDL_GetError() << std::endl;
		return;
	}
	SDL_RenderSetLogicalSize(g_renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	std::cout << "[OK] SDL Renderer created" << std::endl;

	// Init SDL2 Image
	if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG){
		std::cout << "[ERROR] IMG Init: " << IMG_GetError() << std::endl;
		return;
	}
	std::cout << "[OK] IMG Initialized" << std::endl;

	// Stop accepting text input, as it is on by default
	SDL_StopTextInput();

	// If all went ok, set game as running
	m_running = true;

	// Create console text renderer
	m_consoleText = new cText({10, 10});

	// Open lua state
	std::cout << "[INFO] Creating Lua state" << std::endl;
	L = luaL_newstate();

	std::cout << "[OK] Game started corectly" << std::endl;
}

// Destructor quits game
cGame::~cGame(){
	std::cout << "[INFO] Closing Lua state" << std::endl;
	lua_close(L);

	std::cout << "[INFO] Quitting SDL" << std::endl;
	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);
	IMG_Quit();
	SDL_Quit();
}

// Operator() runs game
void cGame::operator()(){
	// TMP 
	m_currentScene = new cSceneBattle;

	// Game loop
	while(m_running){

		// Run scene
		m_currentScene->update(getInput());
		m_currentScene->draw();

		// Draw console
		drawConsole();
	
		// Create frame
		createFrame();
	}
}

// Create single frame of game
void cGame::createFrame(){
	// Create frame tick counter
	static Uint32 previousFrameTicks;

	// Render frame
	SDL_RenderPresent(g_renderer);
	SDL_RenderClear(g_renderer);

	// Wait for enough time to cap FPS
	int waitTime = (1000/FPS) - (SDL_GetTicks() - previousFrameTicks);
	if(waitTime > 0){
		SDL_Delay(waitTime);
	}
	else{
		std::cout << "[INFO] Frame took " << -waitTime << "ms too long" << std::endl;
	}

	// Keep track of ticks at the end of previous frame
	previousFrameTicks = SDL_GetTicks();
}

// Draw console to screen
void cGame::drawConsole(){
	if(SDL_IsTextInputActive()){
		m_consoleText->update("> " + m_command);
		m_consoleText->draw();
	}
}

// Get player input
eBUTTON cGame::getInput(){
	// Process events
	while(SDL_PollEvent(&g_events)){
		// Check for quit request
		if(g_events.type == SDL_QUIT){
			m_running = false;
		}
		// Check for text input events
		else if(SDL_IsTextInputActive()){
			// On enter send command to scene, and end text input
			if(g_events.type == SDL_KEYDOWN and g_events.key.keysym.sym == SDLK_RETURN){
				m_currentScene->command(m_command);
				m_command = "";
				SDL_StopTextInput();
			}
			// On backspace erase last char, if not empty
			if(g_events.type == SDL_KEYDOWN and g_events.key.keysym.sym == SDLK_BACKSPACE and m_command.size() > 0){
				m_command.pop_back();
			}
			// Append char to command
			if(g_events.type == SDL_TEXTINPUT){
				m_command += g_events.text.text;
			}
		}
		// Check for button press events
		else if(g_events.type == SDL_KEYDOWN and g_events.key.repeat == 0){
			switch(g_events.key.keysym.sym){
				case SDLK_RETURN:
				case SDLK_z:
				std::cout << "[INFO] Pressed SELECT" << std::endl;
				return eBUTTON::SELECT;
				break;

				case SDLK_x:
				std::cout << "[INFO] Pressed CANCEL" << std::endl;
				return eBUTTON::CANCEL;
				break;

				case SDLK_c:
				std::cout << "[INFO] Pressed SPECIAL1" << std::endl;
				return eBUTTON::SPECIAL1;
				break;

				case SDLK_v:
				std::cout << "[INFO] Pressed SPECIAL2" << std::endl;
				return eBUTTON::SPECIAL2;
				break;

				case SDLK_ESCAPE:
				std::cout << "[INFO] Pressed ESC" << std::endl;
				return eBUTTON::ESCAPE;
				break;

				case SDLK_F1:
				std::cout << "[INFO] Pressed F1, enabling console input" << std::endl;
				SDL_StartTextInput();
				return eBUTTON::NONE;
				break;
			}
		}
	}

	// Load keys state
	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	static int nUpFrameWait, nDownFrameWait, nRightFrameWait, nLeftFrameWait;

	// Directional buttons
	if(nUpFrameWait > 0)
		nUpFrameWait--;
	else if(keyState[SDL_SCANCODE_UP]){
			std::cout << "[INFO] Up Pressed" << std::endl;
			nUpFrameWait = 6;
			return eBUTTON::UP;
	}
	if(nDownFrameWait > 0)
		nDownFrameWait--;
	else if(keyState[SDL_SCANCODE_DOWN]){
			std::cout << "[INFO] Down Pressed" << std::endl;
			nDownFrameWait = 6;
			return eBUTTON::DOWN;
	}
	if(nRightFrameWait > 0)
		nRightFrameWait--;
	else if(keyState[SDL_SCANCODE_RIGHT]){
			std::cout << "[INFO] Right Pressed" << std::endl;
			nRightFrameWait = 6;
			return eBUTTON::RIGHT;
	}
	if(nLeftFrameWait > 0)
		nLeftFrameWait--;
	else if(keyState[SDL_SCANCODE_LEFT]){
			std::cout << "[INFO] Left Pressed" << std::endl;
			nLeftFrameWait = 6;
			return eBUTTON::LEFT;
	}
	
	// If nothing pressed
	return eBUTTON::NONE;
}
