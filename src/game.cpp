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

	// If all went ok, set game as running
	m_running = true;

	std::cout << "[OK] Game started corectly" << std::endl;
}

// Destructor quits game
cGame::~cGame(){
	std::cout << "[INFO] Quitting SDL" << std::endl;
	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);
	IMG_Quit();
	SDL_Quit();
}

// Operator() runs game
void cGame::operator()(){
	// Init asset manager
	cAssetManager& assets = cAssetManager::getInstance();

	// Game loop
	while(m_running){

		// TMP
		static int i;
		i++;
		if(i == 10000)
			m_running = false;
		// TMP
	}
}
