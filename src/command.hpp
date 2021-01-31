#pragma once

#include "unit.hpp"

//Command interface
class cCommand{
	public:
		virtual ~cCommand() {};
		virtual void execute()=0;			//Command behaviour
		virtual bool isCompleted()=0;			//Return if command was completed
};

//Move direction
class cCommandMove : public cCommand{
	protected:
		cUnit* m_unit;					//Pointer to unit reciving command
		eDIRECTION m_DIRECTION;				//Direction to move
		const int m_vel = 3;				//How many pixel per move frame
		int m_moved = 0;				//How many pixels were traveled
		bool m_completed = false;			//Was command fully executed?
	public:
		cCommandMove(cUnit* p_unit, eDIRECTION p_DIRECTION):
			m_unit(p_unit),
			m_DIRECTION(p_DIRECTION)
			{};
		void execute() override;			//Move m_vel ammount
		bool isCompleted() override;			//Return true when full tile was traveled
};
