#include "globals.hpp"
#include "battle_scene.hpp"
#include "text.hpp"

int main(){
	//Load configuration files
	loadConfig();
	//Initialize game
	g_bGameIsRunning = true;
	if(initGame() == false){
		std::cout << "[ERROR] Failed to initialize " << std::endl;
		g_bGameIsRunning = false;
	}
	else
		loadAssets();

	//Create command propmt text object
	cText prompt({25, g_windowHeight - 25});

	//temporary
	vec2D vMapSize = {27, 23};
	cBattleScene currentScene(vMapSize);
	while(g_bGameIsRunning){
		currentScene.update(getPlayerInput());
		currentScene.draw();
		//draw console propmpt
		if(SDL_IsTextInputActive()){
			prompt.update(">" + g_sConsoleCommand);
			prompt.draw();
		}
		createFrame();
	}

	//Quit game and free assets
	freeAssets();
	quit();
	return 0;
}
