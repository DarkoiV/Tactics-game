#include "action_menu.hpp"

void cActionMenu::showActionMenu(const Uint8 p_possibleActionFlags){
	m_bHidden = false;

	//Add actions based on flags
	if(p_possibleActionFlags & ACTION_ATTACK){
		m_textVector.emplace_back(cText( {0, 0}, 1) );
		m_textVector.back().update("Attack");
		m_actionVector.emplace_back(eACTION::ATTACK);
	}
	if(p_possibleActionFlags & ACTION_MAGIC){
		m_textVector.emplace_back(cText( {0, 0}, 1) );
		m_textVector.back().update("Magic");
		m_actionVector.emplace_back(eACTION::MAGIC);
	}
	if(p_possibleActionFlags & ACTION_HEAL){
		m_textVector.emplace_back(cText( {0, 0}, 1) );
		m_textVector.back().update("Heal");
		m_actionVector.emplace_back(eACTION::HEAL);
	}

	//Wait is always possible!
	m_textVector.emplace_back(cText( {0, 0}, 1) );
	m_textVector.back().update("Wait");
	m_actionVector.emplace_back(eACTION::WAIT);

	//Get lenght of longest text, set height
	vec2D neededCapacity = {0, 0};
	for(auto &TEXT : m_textVector){
		if(TEXT.getTextLenght() > neededCapacity.x)
			neededCapacity.x = TEXT.getTextLenght();
	}
	neededCapacity.y = ((m_textVector[0].getTextHeight() + 2) * m_textVector.size());
	neededCapacity.x += 7;

	//Create box, and center it
	m_box.setCapacity(neededCapacity);
	m_box.centerBox();

	//Position text
	vec2D newPos = m_box.getInnerOrgin();
	for(auto &TEXT : m_textVector){
		TEXT.setNewOriginPoint(newPos);
		newPos.y += TEXT.getTextHeight() + 1;
	}

	//Set color of selected text
	m_textVector[0].changeTextColor(2);
}

//Hide and reset action menu
void cActionMenu::hideActionMenu(){
	m_bHidden = true;
	m_nSelected = 0;
	m_textVector.clear();
	m_actionVector.clear();
}

//Get selected action
eACTION cActionMenu::getSelectedAction(){
	std::cout << "[INFO] Selected " << m_nSelected << std::endl;
	return m_actionVector[m_nSelected];
}

//Move selected option up
void cActionMenu::movSelectionUP(){
	if(m_nSelected > 0){
		std::cout << "[INFO] Moving menu selection up" << std::endl;
		m_textVector[m_nSelected].changeTextColor(1);
		m_nSelected--;
		m_textVector[m_nSelected].changeTextColor(2);
	}
	else
		std::cout << "[INFO] Selection already at top" << std::endl;
}

//Move selected option down
void cActionMenu::movSelectionDOWN(){
	if(m_nSelected < (int)m_textVector.size() - 1){
		std::cout << "[INFO] Moving menu selection down" << std::endl;
		m_textVector[m_nSelected].changeTextColor(1);
		m_nSelected++;
		m_textVector[m_nSelected].changeTextColor(2);
	}
	else
		std::cout << "[INFO] Selection already at bottom" << std::endl;
}

//Draw if not hidden
void cActionMenu::draw(){
	if(not m_bHidden){
		m_box.draw();
		for(auto &TEXT : m_textVector)
			TEXT.draw();
	}
}
