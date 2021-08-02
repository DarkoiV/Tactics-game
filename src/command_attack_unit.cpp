#include "command_attack_unit.hpp"

// Constructor
cCommandAttack::cCommandAttack(cUnit* p_attacking, cUnit* p_target, cBattleLua &L): 
	Lua(L), m_attackingUnit(p_attacking), m_targetUnit(p_target) {
		// Get first item in inventory
		auto weapon = m_attackingUnit->inventory().getFirstItem();

		if(weapon == nullptr) {
			std::cout << "[ERROR] No item in inventory" << std::endl;
			m_completed = true;
			return;
		}

		std::cout << "[INFO] Attacking UNIT " << std::endl;

		// Get weapon by name
		lua_getglobal(Lua(), weapon->name.c_str());
		if (not lua_istable(Lua(), -1)) {
			std::cout << "[ERROR] There is no item table: " << weapon->name << std::endl;
			m_completed = true;
			return;
		}

		// Get attack method, and switch its position with weapon arg
		lua_getfield(Lua(), -1, "Attack");
		lua_insert(Lua(), -2);

		// Push attackingUnit param and targetUnit param
		lua_pushlightuserdata(Lua(), m_attackingUnit);
		lua_pushlightuserdata(Lua(), m_targetUnit);

		// Call attack function
		if (lua_isfunction(Lua(), -4)) {
			if (lua_pcall(Lua(), 3, 1, 0) != 0)
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
