-- DEFAULT ATTACK ------------------------------------

DEFAULT_ATTACK = function()

end

-- IRON SPEAR ----------------------------------------

IRON_SPEAR = {
	name  = "Iron Spear",
	iType = 1,		-- Item Type 0000 0001
	power = 2,
	actions = {
		"Attack"
	}
}

IRON_SPEAR["Attack"] = DEFAULT_ATTACK

-- IRON SWORD ----------------------------------------

IRON_SWORD = {
	name  = "Iron Sword",
	iType = 2,		-- Item Type 0000 0010
	power = 2,
	actions = {
		"Attack"
	}
}

IRON_SWORD["Attack"] = DEFAULT_ATTACK

-- IRON AXE ------------------------------------------

IRON_AXE = {
	name  = "Iron Axe",
	iType = 4,		-- Item Type 0000 0100
	power = 2,
	actions = {
		"Attack"
	}
}

IRON_AXE["Attack"] = DEFAULT_ATTACK
