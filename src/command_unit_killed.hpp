#pragma once

#include "command.hpp"
#include "unit.hpp"

#include <memory>

class cCommandUnitKilled : public cCommand {
	private:
		std::shared_ptr<cUnit> m_unit;

		int m_frameCounter = 0;

	public:
		// Constructor
		cCommandUnitKilled(std::shared_ptr<cUnit> p_unit);
		
		void execute()     override;
		bool isCompleted() override;
};
