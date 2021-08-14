#include "command_attack_unit.hpp"
#include "unit.hpp"

// Constructor
cCommandAttack::cCommandAttack(cUnit* p_attacking, cUnit* p_target, cBattleLua &L): Lua(L) {
		std::cout << "[INFO] Attacking UNIT " << std::endl;

		// get attack sequence 
		lua_getglobal(Lua(), "ATTACK_SEQUENCE");

		// Push attacker param and target param
		cUnit::pushTaggedUnit(Lua(), p_attacking);
		cUnit::pushTaggedUnit(Lua(), p_target);

		// Call attack function
		if (lua_isfunction(Lua(), -3)) {
			if (lua_pcall(Lua(), 2, 1, 0) != 0)
				std::cout << "[ERROR] Running function " << lua_tostring(Lua(), -1) << std::endl;	
		}
		else {
			std::cout << "[ERROR] Not a Lua function " << std::endl;
			m_completed = true;
		}
}

// Execute command
void cCommandAttack::execute() {
	// Clone coroutine function to keep closure
	lua_pushvalue(Lua(), -1);

	if(lua_isfunction(Lua(), -1)) {
		if(lua_pcall(Lua(), 0, 1, 0) != 0)
			std::cout << "[ERROR] Running coroutine " << lua_tostring(Lua(), -1) << std::endl;	
	}
	else
		std::cout << "[ERROR] Not a Lua coroutine " << std::endl;

	// Check return code
	if(lua_isnumber(Lua(), -1)) {
		if(lua_tointeger(Lua(), -1) == -1) {
			m_completed = true;
			lua_pop(Lua(), 1);		// Pop function
		}
			
		lua_pop(Lua(), 1);			// Pop return code
	}
	else {
		std::cout << "[ERROR] No return code from LUA coroutine, terminating" << std::endl;
		lua_pop(Lua(), -1);
		m_completed = true;
	}
}

// Is commnad completed
bool cCommandAttack::isCompleted() {
	return m_completed;
}
