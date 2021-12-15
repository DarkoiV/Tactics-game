#pragma once

#include <cstdint>

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

// Directions
enum class eDIRECTION{
	NORTH,
	EAST,
	SOUTH,
	WEST
};

// Colors of text
enum class eTEXT_COLOR{
	RED,
	YELLOW
};

// Item types
enum class eITEM : uint8_t {
	SPEAR  = 0b0000'0001,		// Bonus anti armor
	SWORD  = 0b0000'0010,		// Default
	AXE    = 0b0000'0100,		// Higher crit, lower accuracy
	BOW    = 0b0000'1000,		// 2-4 range
	STAFF  = 0b0001'0000,		// Buffs
	BOOK   = 0b0010'0000,		// Magic distance attack
	ORB    = 0b0100'0000,		// Magic high crit near attack
	POTION = 0b1000'0000		// Self use
};

// Action types
enum class eACTION {
	ATTACK,
	HEAL,
	USE,
	WAIT,
	RETURN
};
