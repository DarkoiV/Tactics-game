#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//SDL variables and constans used for rendering
#define FPS 60
#define TILE_SIZE 24
inline SDL_Window* g_window;
inline SDL_Renderer* g_renderer;
inline int g_windowWidth = 576;
inline int g_windowHeight = 360;
inline int g_nScaleFactor = 2;

//SDL variables and constans used for events
inline bool g_bGameIsRunning = true;
inline bool g_bConsoleCommandIssued = false;
inline std::string g_sConsoleCommand = "";
inline SDL_Event g_event;
enum class eBUTTON;

//Global assets
inline SDL_Texture* g_pConsoleTextTexture = nullptr;
inline SDL_Texture* g_pRangeTileset = nullptr;

//Functions
void loadConfig();
bool initGame();
void loadAssets();
void freeAssets();
SDL_Texture* loadSprite(std::string p_sPath);
eBUTTON getPlayerInput();
void createFrame();
void quit();

//Structures for use in game
struct vec2D{
	int x;
	int y;
};

inline std::ostream& operator << (std::ostream &os, const vec2D &s){
	return (os << s.x << "x" << s.y);
}

struct sTile{
	int typeID;
	int movCost;
};

enum class eBUTTON{
	UP,
	DOWN,
	RIGHT,
	LEFT,
	SELECT,
	CANCEL,
	SPECIAL,
	SPECIAL2,
	ESCAPE,
	NONE
};

enum class eDIRECTION{
	NORTH,
	SOUTH,
	EAST,
	WEST
};
