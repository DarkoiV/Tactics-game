require("data/items/sequences")

-- IRON SWORD ----------------------------------------

IRON_BOW = {
	name     = "Iron Bow",
	iType    = WEAPON_BOW,
	power    = 2,
	pierce   = 0,
	minRange = 2,
	maxRange = 3,
	action   = "Attack"
}

IRON_BOW["Attack"]  = DEFAULT_ATTACK
IRON_BOW["Counter"] = DEFAULT_ATTACK
