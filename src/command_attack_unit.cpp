#include "command_attack_unit.hpp"

// Constructor
cCommandAttack::cCommandAttack(cUnit* p_attacking, cUnit* p_target, cBattleLua &L): 
	Lua(L), m_attackingUnit(p_attacking), m_targetUnit(p_target) {

		std::cout << "[INFO] Attacking UNIT " << std::endl;

		lua_getglobal(Lua(), "DEFAULT_ATTACK");			// Get attack
		lua_getglobal(Lua(), "IRON_SWORD");			// Weapon arg
		lua_pushlightuserdata(Lua(), m_attackingUnit);		// Attacking Unit arg
		lua_pushlightuserdata(Lua(), m_targetUnit);		// Target unit arg
		if(lua_isfunction(Lua(), -4)){
			if (lua_pcall(Lua(), 3, 1, 0) != 0)
				std::cout << "[ERROR] Running function " << lua_tostring(Lua(), -1) << std::endl;	
		}
		else
			std::cout << "[ERROR] Not a Lua function " << std::endl;
}

// Execute command
void cCommandAttack::execute() {
	// Clone coroutine function to keep closure
	lua_pushvalue(Lua(), -1);

	if(lua_isfunction(Lua(), -1)){
		if(lua_pcall(Lua(), 0, 1, 0) != 0)
			std::cout << "[ERROR] Running coroutine " << lua_tostring(Lua(), -1) << std::endl;	
	}
	else
		std::cout << "[ERROR] Not a Lua coroutine " << std::endl;

	// Check return code
	if(lua_isnumber(Lua(), -1)){
		if(lua_tointeger(Lua(), -1) == -1){
			m_completed = true;
			lua_pop(Lua(), 1);		// Pop function
		}
			
		lua_pop(Lua(), 1);			// Pop return code
	}
	else std::cout << "[WARN] NO RETURN CODE !!" << std::endl;
}

// Is commnad completed
bool cCommandAttack::isCompleted() {
	return m_completed;
}
