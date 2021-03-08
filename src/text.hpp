#pragma once

#include "globals.hpp"
#include "asset_manager.hpp"

//All text sprites have to follow this:
#define CHARS_PER_COLUMN 6
#define CHARS_PER_ROW 16

class cText{
	protected:
		std::string m_sTextToRender = "";		//String with chars to render
		vec2D m_vCharacterSize;				//Size od individual char in pixels
		vec2D m_vOriginPoint;				//Where does text start

		bool m_bUsingColorText = false;	
		int m_nLastPossibleColor = 2;			//Which color is last possible to access
		int m_nScaleOfText = 1;				//Scale of text to display

		SDL_Texture* m_pTextSprite;			//Pointer to text texture

	public:
		//Constructore/destructor
		cText(const vec2D p_vOriginPoint);		//Default constructor
		cText(const vec2D p_vOriginPoint, int p_nColor);
		cText(const vec2D p_vOriginPoint, int p_nColor, int p_nScale);
		~cText();

		//Methods
		int getTextLenght();				//Returns lenght of text in pixels
		int getTextHeight();				//Returns height of character in pixels

		void changeTextColor(int p_nColor);			//Changes color of text
		void setNewOriginPoint(vec2D p_vNewOriginPoint);	//Set new origin point of text

		void update(const std::string p_sNewText);
		void draw();


};
