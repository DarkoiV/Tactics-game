#pragma once

#include "lua.hpp"

class cBattleLua{
	private:
		lua_State* L;
	public:
		// Constructor opens lua state
		cBattleLua();

		// Destructor closes lua state
		~cBattleLua();

		// Get lua state
		auto operator()() -> lua_State*;
};
