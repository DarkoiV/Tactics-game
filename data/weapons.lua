require("data/fn")

-- WEAPON TYPES --------------------------------------

local WEAPON_SPEAR = 1		-- 0000 0001
local WEAPON_SWORD = 2		-- 0000 0010
local WEAPON_AXE   = 4		-- 0000 0100

-- ATTACK SEQUENCE -----------------------------------

ATTACK_SEQUENCE = function(attacker, target)
	print("[LUA] Creating coroutine")

	-- CREATE COROUTINE OF ATTACK SEQUENCE -------
	local co = coroutine.create(function()
		local weapon = attacker:getItem()

		-- Attack with weapon
		print("[Lua] Attakcing with " .. weapon.name)
		weapon.Attack(attacker, target)

		-- Check if counter possible
		local targetItem = target:getItem()
		local targetHP   = target:getHP()

		if targetItem.Counter ~= nil and targetHP > 0 then
			print("[LUA] Counter with " .. targetItem.name)
			targetItem.Counter(target, attacker)
		end
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

-- DEFAULT ATTACK ------------------------------------

DEFAULT_ATTACK = function(attacker, target)
	-- Get weapon
	local weapon = attacker:getItem()

	-- ANIMATE
	local movX, movY
	local aX, aY = attacker:getPos()
	local tX, tY = target:getPos()
	movX = aX - tX
	movY = aY - tY

	for _ = 1, 8 do
		attacker:offset(movX, movY)
		Fn.wait(2)
	end

	attacker:offset((-movX) * 4, (-movY) * 4)
	Fn.wait(2)

	attacker:resetOffset()
	Fn.wait(1)

	target:offset(3 * (-movX), 3 * (-movY))
	Fn.wait(4)

	target:resetOffset()

	-- DEAL DAMAGE
	local aSTR, _ = attacker:getPhysical()
	local _, tDEF = target:getPhysical()

	local armorAfterPierce = tDEF - weapon.pierce
	if armorAfterPierce < 0 then armorAfterPierce = 0 end

	local damage = aSTR + weapon.power - armorAfterPierce
	if damage < 0 then damage = 0 end

	target:damage(damage)
	print("[LUA] Dealt " .. damage .. " damage to unit")

	Fn.wait(5);
end

-- IRON SPEAR ----------------------------------------

IRON_SPEAR = {
	name     = "Iron Spear",
	iType    = WEAPON_SPEAR,
	power    = 1,
	pierce   = 2,
	minRange = 1,
	maxRange = 1,
	actions  = {
		"Attack"
	}
}

IRON_SPEAR["Attack"]  = DEFAULT_ATTACK
IRON_SPEAR["Counter"] = DEFAULT_ATTACK

-- IRON SWORD ----------------------------------------

IRON_SWORD = {
	name     = "Iron Sword",
	iType    = WEAPON_SWORD,
	power    = 2,
	pierce   = 0,
	minRange = 1,
	maxRange = 1,
	actions  = {
		"Attack"
	}
}

IRON_SWORD["Attack"]  = DEFAULT_ATTACK
IRON_SWORD["Counter"] = DEFAULT_ATTACK

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
