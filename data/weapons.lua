-- WEAPON TYPES --------------------------------------

local WEAPON_SPEAR = 1		-- 0000 0001
local WEAPON_SWORD = 2		-- 0000 0010
local WEAPON_AXE   = 4		-- 0000 0100

-- DEFAULT ATTACK ------------------------------------

DEFAULT_ATTACK = function(weapon, attackingUnit, targetUnit)
	print("[LUA] Creating coroutine")

	-- create coroutine of attack
	local co = coroutine.create(function()
		print("[LUA] Attacking with", weapon["name"])
		coroutine.yield()

		-- Wait one minute
		for i = 1, 60 do
			coroutine.yield()
		end
	end)

	-- return anonymous function that will manage coroutine
	return function()
		if coroutine.status(co) == "dead" then
			print("[LUA] Coroutine ended")
			return -1
		end

		coroutine.resume(co)
		return 0
	end
end

-- IRON SPEAR ----------------------------------------

IRON_SPEAR = {
	name  = "Iron Spear",
	iType = WEAPON_SPEAR,
	power = 2,
	actions = {
		"Attack"
	}
}

IRON_SPEAR["Attack"] = DEFAULT_ATTACK

-- IRON SWORD ----------------------------------------

IRON_SWORD = {
	name  = "Iron Sword",
	iType = WEAPON_SWORD,
	power = 2,
	actions = {
		"Attack"
	}
}

IRON_SWORD["Attack"] = DEFAULT_ATTACK

-- IRON AXE ------------------------------------------

IRON_AXE = {
	name  = "Iron Axe",
	iType = WEAPON_AXE,
	power = 2,
	actions = {
		"Attack"
	}
}

IRON_AXE["Attack"] = DEFAULT_ATTACK
