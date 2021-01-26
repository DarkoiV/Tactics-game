#include "globals.hpp"
#include "map.hpp"

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
	cMap testMap("testMap");
	while(g_bGameIsRunning){
		testMap.update(getPlayerInput());
		testMap.draw();
		createFrame();
	}

	//Quit game
	quit();
	return 0;
}
