require("data/fn")

-- WEAPON TYPES --------------------------------------

local WEAPON_SPEAR = 1		-- 0000 0001
local WEAPON_SWORD = 2		-- 0000 0010
local WEAPON_AXE   = 4		-- 0000 0100

-- DEFAULT ATTACK ------------------------------------

DEFAULT_ATTACK = function(weapon, attackingUnit, targetUnit)
	print("[LUA] Creating coroutine")

	-- CREATE COROUTINE OF ATTACK ----------------
	local co = coroutine.create(function()
		-- ANIMATE
		local movX, movY
		local aX, aY = Unit.getPos(attackingUnit)
		local tX, tY = Unit.getPos(targetUnit)
		movX = aX - tX
		movY = aY - tY

		for _ = 1, 8 do
			Unit.offset(attackingUnit, movX, movY)
			Fn.wait(2)
		end

		Unit.offset(attackingUnit, (-movX) * 4, (-movY) * 4)
		Fn.wait(2)

		Unit.resetOffset(attackingUnit)
		Fn.wait(1)

		Unit.offset(targetUnit, 3 * (-movX), 3 * (-movY))
		Fn.wait(4)

		Unit.resetOffset(targetUnit)

		-- DEAL DAMAGE
		local aSTR, _ = Unit.getPhysical(attackingUnit)
		local _, tDEF = Unit.getPhysical(targetUnit)

		local armorAfterPierce = tDEF - weapon.pierce
		if armorAfterPierce < 0 then armorAfterPierce = 0 end

		local damage = aSTR + weapon.power - armorAfterPierce
		if damage < 0 then damage = 0 end

		Unit.damage(targetUnit, damage)
		print("[LUA] Dealt " .. damage .. " damage to unit")

		Fn.wait(5);
	end)
	-- END OF COUROUTINE -------------------------

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
	name    = "Iron Spear",
	iType   = WEAPON_SPEAR,
	power   = 1,
	pierce  = 2,
	actions = {
		"Attack"
	}
}

IRON_SPEAR["Attack"] = DEFAULT_ATTACK

-- IRON SWORD ----------------------------------------

IRON_SWORD = {
	name    = "Iron Sword",
	iType   = WEAPON_SWORD,
	power   = 2,
	pierce  = 0,
	actions = {
		"Attack"
	}
}

IRON_SWORD["Attack"] = DEFAULT_ATTACK

-- IRON AXE ------------------------------------------

IRON_AXE = {
	name    = "Iron Axe",
	iType   = WEAPON_AXE,
	power   = 2,
	pierce  = 0,
	actions = {
		"Attack"
	}
}

IRON_AXE["Attack"] = DEFAULT_ATTACK
