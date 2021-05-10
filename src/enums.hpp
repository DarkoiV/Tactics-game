#pragma once

#include <cstdint>

// Scene types in game
enum class eSCENE {
	MAIN_MENU,
	SETTINGS,
	BATTLE,
	EDIT
};

// Button types
enum class eBUTTON {
	SELECT,
	CANCEL,
	ESCAPE,
	UP,
	DOWN,
	RIGHT,
	LEFT,
	SPECIAL1,
	SPECIAL2,
	NONE
};

// Item types
enum class eITEM : uint8_t {
	SPEAR  = 0b00000001,		// Bonus anti armor
	SWORD  = 0b00000010,		// Default
	AXE    = 0b00000100,		// Higher crit, lower accuracy
	STAFF  = 0b00001000,		// Buffs
	BOOK   = 0b00010000,		// Magic distance attack
	ORB    = 0b00100000,		// Magic high crit near attack
	POTION = 0b01000000		// Self use
};
