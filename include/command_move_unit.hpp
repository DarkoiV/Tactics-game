#pragma once

#include "command.hpp"
#include "unit.hpp"
#include "enums.hpp"

class cCommandMove : public cCommand{
	protected:
		cUnit*     m_unit;				//Pointer to unit reciving command
		eDIRECTION m_DIRECTION;				//Direction to move

		static constexpr int VELOCITY = 3;		//How many pixel to move frame

		int m_traveled = 0;				//How many pixels were traveled
	public:
		// Constructor sets unit commanded, and direction of move
		cCommandMove(cUnit* p_unit, eDIRECTION p_DIRECTION):
			m_unit(p_unit),
			m_DIRECTION(p_DIRECTION)
			{};

		// Methods
		void execute()     override;			//Move m_vel ammount
		bool isCompleted() override;			//Return true when full tile was traveled
};
