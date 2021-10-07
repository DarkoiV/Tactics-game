#pragma once

#include <cstdint>

// Unit stats
struct sStats{
	uint8_t HP;		// Health Points
	uint8_t MP;		// Mana Points
	uint8_t MHP;		// Max HP
	uint8_t MMP;		// Max MP
	uint8_t DEF;		// Defence     (for physical Defence)
	uint8_t STR;		// Strenght    (for physical DMG)
	uint8_t AGI;		// Agility     (for accuracy, and dodge)
	uint8_t INT;		// Inteligence (for magical DEF/DMG)
	uint8_t MOV;		// Movement range 
};
