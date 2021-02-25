#pragma once

#include <vector>

#include "globals.hpp"
#include "ui_box.hpp"
#include "text.hpp"

class cActionMenu{
	protected:
		cBox m_box;
		std::vector<cText> m_textVector;

		bool m_bHidden = true;

		int m_nSelected = 0;

	public:
		
		//Methods
		void showActionMenu(const Uint8 p_possibleActionFlags);

		bool isHidden(){return m_bHidden;}; 

		int getSelectedAction();

		void hideActionMenu();

		void draw();
};
