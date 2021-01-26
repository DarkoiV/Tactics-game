#include "globals.hpp"

//Load configuration from file
void loadConfig(){
}

//Initialize SDL, return false if something went wrong
bool initGame(){
	//Initalize video and audio
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0){
		std::cout <<"[ERROR] SDL Init: " << SDL_GetError() << std::endl;
		return false;
	}
	std::cout << "[OK] SDL Init" << std::endl;
	//Initialize IMG
	if(IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG){
		std::cout << "[ERROR] IMG Init: " << IMG_GetError() << std::endl;
		return false;
	}
	std::cout << "[OK] IMG Init" << std::endl;
	//Create Window
	g_window = SDL_CreateWindow("TITLE", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
			g_windowWidth * g_nScaleFactor, g_windowHeight * g_nScaleFactor, 0);
	if(g_window == NULL){
		std::cout << "[ERROR] SDL Window: " << SDL_GetError() << std::endl;
		return false;
	}
	std::cout << "[OK] SDL Global window created" << std::endl;
	//Create Renderer
	g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
	if(g_renderer == NULL){
		std::cout << "[ERROR] SDL Renderer: " << SDL_GetError() << std::endl;
		return false;
	}
	SDL_RenderSetLogicalSize(g_renderer, g_windowWidth, g_windowHeight);
	std::cout << "[OK] Global renderer created" << std::endl;
	return true;
}

//Load all global assets
void loadAssets(){
}

//Load texture
SDL_Texture* loadSprite(std::string p_path){
	SDL_Surface* loadingSurface;
	loadingSurface = IMG_Load(p_path.c_str());
	if(loadingSurface == NULL){
		std::cout << "[ERROR] " << p_path << " not loaded: " << IMG_GetError() << std::endl;
		return NULL;
	}
	SDL_Texture* loadedSprite = SDL_CreateTextureFromSurface(g_renderer, loadingSurface);
	if(loadedSprite == NULL){
		std::cout << "[ERROR] "<< p_path << " texture creation failed: " << IMG_GetError() << std::endl;
		return NULL;
	}
	SDL_FreeSurface(loadingSurface);
	std::cout << "[OK] " << p_path << " loaded correctly" << std::endl;
	return loadedSprite;
}

//Create frame, wait if calculations went too fast
void createFrame(){
	static Uint32 previousFrameTicks;
	SDL_RenderPresent(g_renderer);
	SDL_RenderClear(g_renderer);
	int waitTime = (1000/FPS) - (SDL_GetTicks() - previousFrameTicks);
	if(waitTime > 0){
		SDL_Delay(waitTime);
	}
	previousFrameTicks = SDL_GetTicks();
}

//Return pressed button
eBUTTON getPlayerInput(){
	//Check if player closed game
	while(SDL_PollEvent(&g_event)){
		if(g_event.type == SDL_QUIT)
			g_bGameIsRunning = false;
	}

	//Return none if no button pressed
	return eBUTTON::NONE;
}

//Quit. free memory
void quit(){
	std::cout << "[INFO] Quiting game" << std::endl;
	SDL_DestroyRenderer(g_renderer);
	SDL_DestroyWindow(g_window);
	
	IMG_Quit();
	SDL_Quit();
}
