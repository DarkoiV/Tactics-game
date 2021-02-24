#pragma once

#include <vector>

#include "globals.hpp"
#include "ui_box.hpp"
#include "text.hpp"

class cActionMenu{
	protected:
		cBox m_box;
		std::vector<cText> m_textVector;

	public:
		cActionMenu();
		void draw();
};
