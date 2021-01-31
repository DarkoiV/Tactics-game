#pragma once

#include "globals.hpp"

//All text sprites have to follow this:
#define CHARS_PER_COLUMN 6
#define CHARS_PER_ROW 16

class cText{
	protected:
		std::string m_sTextToRender = "";		//String with chars to render
		vec2D m_vCharacterSize;				//Size od individual char in pixels
		vec2D m_vOriginPoint;				//Where does text start

		SDL_Texture* m_pTextSprite;			//Pointer to text texture

	public:
		//Constructore/destructor
		cText(const vec2D p_vOriginPoint);
		~cText();

		//Methods
		void update(const std::string p_sNewText);
		void draw();


};