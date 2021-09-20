#pragma once

#include "unit.hpp"
#include "battle_lua.hpp"
#include "enums.hpp"

class cActionMenu {
	private:
		cBattleLua &Lua;

	public:
		cActionMenu(cBattleLua &L):
			Lua(L){};

		void moveUp();
		void moveDown();
		void moveRight();
		void moveLeft();

		void select();
		void cancel();

		void operator[](cUnit* p_unit);

		bool isSelected();
		auto getSelectedAction() -> eACTION;



		void draw();
};
