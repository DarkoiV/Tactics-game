#include "globals.hpp"
#include "battle_scene.hpp"

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

	//temporary
	vec2D vMapSize = {27, 23};
	cBattleScene currentScene(vMapSize);
	while(g_bGameIsRunning){
		currentScene.update(getPlayerInput());
		currentScene.draw();
		createFrame();
	}

	//Quit game
	quit();
	return 0;
}
