require("data/items/sequences")

-- IRON AXE ------------------------------------------

IRON_AXE = {
	name     = "Iron Axe",
	iType    = WEAPON_AXE,
	power    = 2,
	pierce   = 0,
	minRange = 1,
	maxRange = 1,
	actions  = {
		"Attack"
	}
}

IRON_AXE["Attack"]  = DEFAULT_ATTACK
IRON_AXE["Counter"] = DEFAULT_ATTACK
