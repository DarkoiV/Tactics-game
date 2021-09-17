require("data/items/sequences")

-- IRON SPEAR ----------------------------------------

IRON_SPEAR = {
	name     = "Iron Spear",
	iType    = WEAPON_SPEAR,
	power    = 1,
	pierce   = 2,
	minRange = 1,
	maxRange = 1,
	action   = "Attack"
}

IRON_SPEAR["Attack"]  = DEFAULT_ATTACK
IRON_SPEAR["Counter"] = DEFAULT_ATTACK
