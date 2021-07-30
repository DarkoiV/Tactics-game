#pragma once

#include "command.hpp"
#include "unit.hpp"
#include "battle_lua.hpp"

class cCommandAttack : public cCommand {
	protected:
		// ~ LUA ~
		cBattleLua &Lua;

		// Units
		cUnit* m_attackingUnit;
		cUnit* m_targetUnit;

		// Weapon
		std::string m_weapon;

		bool m_completed = false;
	public:
		// Constructor
		cCommandAttack(cUnit* p_attacking, cUnit* p_target, cBattleLua &L, const std::string &p_weapon);

		// Methods
		void execute()		override;
		bool isCompleted()	override;
};
