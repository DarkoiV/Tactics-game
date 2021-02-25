#include "action_menu.hpp"

void cActionMenu::showActionMenu(const Uint8 p_possibleActionFlags){
	m_bHidden = false;

	//Add actions based on flags
	if(p_possibleActionFlags & ACTION_ATTACK){
		m_textVector.emplace_back(cText( {0, 0}, 1) );
		m_textVector.back().update("Attack");
	}
	if(p_possibleActionFlags & ACTION_MAGIC){
		m_textVector.emplace_back(cText( {0, 0}, 1) );
		m_textVector.back().update("Magic");
	}
	if(p_possibleActionFlags & ACTION_HEAL){
		m_textVector.emplace_back(cText( {0, 0}, 1) );
		m_textVector.back().update("Heal");
	}

	//Wait is always possible!
	m_textVector.emplace_back(cText( {0, 0}, 1) );
	m_textVector.back().update("Wait");

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
}

//Get selected action
int cActionMenu::getSelectedAction(){
	//For now return 0 which is equivalent to wait
	return 0;
}

//Hide and reset action menu
void cActionMenu::hideActionMenu(){
	m_bHidden = true;
	m_nSelected = 0;
	m_textVector.clear();
}

//Draw if not hidden
void cActionMenu::draw(){
	if(not m_bHidden){
		m_box.draw();
		for(auto &TEXT : m_textVector)
			TEXT.draw();
	}
}
