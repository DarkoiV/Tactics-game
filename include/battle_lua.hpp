#pragma once

#include "lua.hpp"

class cBattleLua{
	private:
		lua_State* L;
	public:
		// Constructor opens lua state
		cBattleLua();

		cBattleLua(cBattleLua&) = delete;
		cBattleLua(cBattleLua&&) = delete;

		// Destructor closes lua state
		~cBattleLua();

		// Get lua state
		auto operator()() -> lua_State*;
};
