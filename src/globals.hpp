#pragma once

#include <SDL2/SDL.h>
#include <iostream>

//Constants
constexpr int FPS           = 60 ;
constexpr int TILE_SIZE     = 24 ; //in pixels
constexpr int WINDOW_WIDTH  = 576; 
constexpr int WINDOW_HEIGHT = 360;

//Variables
inline SDL_Window*   g_window  ;
inline SDL_Renderer* g_renderer;

inline int g_scaleFactor      = 2 ;
inline std::string g_basePath = "";
