#include "game.hpp"
#include "asset_manager.hpp"

auto main() -> int{
	// Create game object
	cGame game;

	// Run game
	game();

	// Free resources
	game.freeResources();
}
