#pragma once

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

//SDL variables and constans
#define FPS 60
#define TILE_SIZE 24
inline SDL_Window* g_window;
inline SDL_Renderer* g_renderer;
inline SDL_Event g_event;
inline int g_windowWidth = 576;
inline int g_windowHeight = 360;
inline bool g_bGameIsRunning = true;
inline int g_nScaleFactor = 2;
enum class eBUTTON;

//Functions
void loadConfig();
bool initGame();
void loadAssets();
SDL_Texture* loadSprite(std::string p_path);
eBUTTON getPlayerInput();
void createFrame();
void quit();

//Structures for use in game
struct vec2D{
	int x;
	int y;
};

struct sTile{
	int typeID;
	int movCost;
	int x;
	int y;
};

enum class eBUTTON{
	UP,
	DOWN,
	RIGHT,
	LEFT,
	SELECT,
	CANCEL,
	ESCAPE,
	NONE
};
