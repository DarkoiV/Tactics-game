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
	//Disable SDL text input, because for some reason it is on by default
	SDL_StopTextInput();
	return true;
}

//Load all global assets
void loadAssets(){
	//Conole text
	g_pConsoleTextTexture = loadSprite("graphics/consoleText.png");
	//Range tileset
	g_pRangeTileset = loadSprite("graphics/range.png");
	SDL_SetTextureAlphaMod(g_pRangeTileset, 125);
}

//Free all global assets
void freeAssets(){
	SDL_DestroyTexture(g_pConsoleTextTexture);
	SDL_DestroyTexture(g_pRangeTileset);
}

//Load sprite
SDL_Texture* loadSprite(std::string p_sPath){
	SDL_Surface* loadingSurface;
	loadingSurface = IMG_Load(p_sPath.c_str());
	if(loadingSurface == NULL){
		std::cout << "[ERROR] " << p_sPath << " not loaded: " << IMG_GetError() << std::endl;
		return NULL;
	}
	SDL_Texture* loadedSprite = SDL_CreateTextureFromSurface(g_renderer, loadingSurface);
	if(loadedSprite == NULL){
		std::cout << "[ERROR] "<< p_sPath << " texture creation failed: " << IMG_GetError() << std::endl;
		return NULL;
	}
	SDL_FreeSurface(loadingSurface);
	std::cout << "[OK] " << p_sPath << " loaded correctly" << std::endl;
	return loadedSprite;
}

//Create frame, wait for consistent frame rate
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
	//Check if anything used command
	if(g_bConsoleCommandIssued){
		std::cout << "[WARNING] '" << g_sConsoleCommand << "' not recognized here" << std::endl;
		g_bConsoleCommandIssued = false;
	}
	//Event buttons
	while (SDL_PollEvent(&g_event)){
		//Check if asked for quit
		if(g_event.type == SDL_QUIT){
			g_bGameIsRunning = false;
		}
		//Process console command input
		if(SDL_IsTextInputActive()){
			//Send console command
			if(g_event.type == SDL_KEYDOWN and g_event.key.keysym.sym == SDLK_RETURN){
				std::cout << "[INFO] Command issued: " << g_sConsoleCommand << std::endl;
				g_bConsoleCommandIssued = true;
				SDL_StopTextInput();
			}
			if(g_event.type == SDL_KEYDOWN and g_event.key.keysym.sym == SDLK_BACKSPACE and g_sConsoleCommand.size() > 0){
				g_sConsoleCommand.pop_back();
			}
			if(g_event.type == SDL_TEXTINPUT){
				g_sConsoleCommand += g_event.text.text;
			}
		}
		//Check key presses 
		else if(g_event.type == SDL_KEYDOWN and g_event.key.repeat == 0){
			switch(g_event.key.keysym.sym){
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
				std::cout << "[INFO] Pressed SPECIAL" << std::endl;
				return eBUTTON::SPECIAL;
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
				std::cout << "[INFO] Pressed CONSOLE COMMAND" << std::endl;
				//Start accepting console input and empty string
				g_sConsoleCommand = "";
				SDL_StartTextInput();
				return eBUTTON::NONE;
				break;
			}
		}
	}
	//Load state
	const Uint8* keyState = SDL_GetKeyboardState(NULL);
	static int nUpFrameWait, nDownFrameWait, nRightFrameWait, nLeftFrameWait;

	//Directional buttons
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


	//If none was pressed
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
