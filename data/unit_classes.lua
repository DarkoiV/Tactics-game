require("data/items/sequences")

INFANTRY = {
	hp = 15,
	mp = 10,
	def = 2,
	str = 2,
	agi = 2,
	int = 2,
	mov = 5,
	use = {
		WEAPON_SPEAR,
		ITEM_POTION
	},
	gear = {
		"IRON_SPEAR"
	}
}

ARCHER = {
	hp = 10,
	mp = 10,
	def = 1,
	str = 1,
	agi = 3,
	int = 2,
	mov = 5,
	use = {
		WEAPON_BOW,
		ITEM_POTION
	},
	gear = {
		"IRON_BOW"
	}
}
