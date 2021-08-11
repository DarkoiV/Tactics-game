#pragma once

#include "command.hpp"
#include "enums.hpp"
#include "unit.hpp"
#include "animator.hpp"
#include "battle_lua.hpp"

#include <queue>
#include <stack>
#include <memory>

class cCommander {
	private:
		// Access to lua state
		cBattleLua &Lua;

		// Access to animator
		cAnimator &animator;

		// Queue of commands to execute
		std::queue<std::unique_ptr<cCommand>> m_commandQueue;
	public:
		// Constructor
		cCommander(cBattleLua &Lua, cAnimator &a):
			Lua(Lua),
			animator(a){};

		// Execute command from command queue, return false when no command left
		bool execute();

		// Create commands and add them to queue
		void moveUnit(cUnit* p_movedUnit, std::stack<eDIRECTION> p_directions);

		void attack(cUnit* p_attacking, cUnit* p_target);

		void unitsKilled(int p_howMany);
};
