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

		bool m_completed = false;
	public:
		// Constructor
		cCommandAttack(cUnit* p_attacking, cUnit* p_target, cBattleLua &L);

		// Methods
		void execute()		override;
		bool isCompleted()	override;
};
