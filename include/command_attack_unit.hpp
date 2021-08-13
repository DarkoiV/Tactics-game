#pragma once

#include "command.hpp"
#include "struct_tagged.hpp"
#include "battle_lua.hpp"

class cUnit;

class cCommandAttack : public cCommand {
	protected:
		// ~ LUA ~
		cBattleLua &Lua;

		// Tagged Units
		sTagged m_attackingUnit;
		sTagged m_targetUnit;

		bool m_completed = false;
	public:
		// Constructor
		cCommandAttack(cUnit* p_attacking, cUnit* p_target, cBattleLua &L);

		// Methods
		void execute()		override;
		bool isCompleted()	override;
};
