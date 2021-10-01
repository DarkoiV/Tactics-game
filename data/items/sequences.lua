require("data/fn")

-- ITEM TYPES ----------------------------------------

WEAPON_SPEAR = 1		-- 0000 0001
WEAPON_SWORD = 2		-- 0000 0010
WEAPON_AXE   = 4		-- 0000 0100
WEAPON_BOW   = 8		-- 0000 1000
ITEM_STAFF   = 16		-- 0001 0000
ITEM_BOOK    = 32		-- 0010 0000
ITEM_ORB     = 64		-- 0100 0000
ITEM_POTION  = 128		-- 1000 0000

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
		if targetItem == nil then goto CO_END end
		if targetItem.Counter == nil then goto CO_END end

		local targetHP   = target:getHP()
		if targetHP <= 0 then goto CO_END end

		local aX, aY     = attacker:getPos()
		local tX, tY     = target:getPos()
		local distance = math.abs(aX - tX) + math.abs(aY - tY)

		if distance > targetItem.maxRange
		or distance < targetItem.minRange then
			goto CO_END
		end

		print("[LUA] Counter with " .. targetItem.name)
		targetItem.Counter(target, attacker)

		::CO_END::
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
	movX = movX // math.abs(movX)
	movY = movY // math.abs(movY)
	print (movX .. "x" .. movY)

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
