require("data/items/sequences")

-- IRON SWORD ----------------------------------------

IRON_SWORD = {
	name     = "Iron Sword",
	iType    = WEAPON_SWORD,
	power    = 2,
	pierce   = 0,
	minRange = 1,
	maxRange = 1,
	actions  = "Attack"
}

IRON_SWORD["Attack"]  = DEFAULT_ATTACK
IRON_SWORD["Counter"] = DEFAULT_ATTACK
