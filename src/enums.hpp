#pragma once

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
enum class eITEM {
	SPEAR,		// Bonus anti armor
	SWORD,		// Default
	AXE,		// Higher crit, lower accuracy
	STAFF,		// Buffs
	BOOK,		// Magic distance attack
	ORB,		// Magic high crit near attack
	POTION		// Self use
};
