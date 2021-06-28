#pragma once

#include "lua.hpp"
#include <SDL2/SDL.h>
#include <iostream>

// Constants
constexpr int FPS           = 60 ;
constexpr int TILE_SIZE     = 24 ; //in pixels
constexpr int SCREEN_WIDTH  = 576; 
constexpr int SCREEN_HEIGHT = 360;

// SDL 
inline SDL_Window*   g_window   = nullptr;
inline SDL_Renderer* g_renderer = nullptr;
inline SDL_Event     g_events;

// Variables
inline int g_scaleFactor      = 2 ;
inline std::string g_basePath = "";
inline std::string g_title    = ""; 

// Lua state
inline lua_State* L;
