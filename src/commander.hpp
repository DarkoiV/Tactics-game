#pragma once

#include "command.hpp"
#include <queue>
#include <memory>

class cCommander{
	protected:
		std::queue<std::unique_ptr<cCommand>> m_commandQueue;

	public:
		//Methods
		bool isProcessingCommands();				//Return true when processing commands, and process them
		bool noCommands(){return m_commandQueue.empty();};	//Return true when empty
		
		//add commands
		void moveUnit(cUnit* p_unit, eDIRECTION p_DIRECTION);
};
