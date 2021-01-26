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
	vec2D vMapSize = {25, 20};
	cMap testMap(vMapSize);
	while(g_bGameIsRunning){
		testMap.update(getPlayerInput());
		testMap.draw();
		createFrame();
	}

	//Quit game
	quit();
	return 0;
}
