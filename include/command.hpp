#pragma once

// command interface
class cCommand{
	public:
		virtual ~cCommand() {};
		virtual void execute()=0;			//Command behaviour
		virtual bool isCompleted()=0;			//Return if command was completed
};
