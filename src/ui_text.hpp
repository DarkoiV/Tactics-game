#pragma once

#include "enums.hpp"
#include "struct_vec2D.hpp"
#include <string>
#include <SDL2/SDL_render.h>

class cText{
	protected:
		//All text sprites have to be formated in this way:
		static constexpr int CHARS_PER_COLUMN = 6;
		static constexpr int CHARS_PER_ROW = 16;

		// Rendering variables
		std::string m_textToRender = "";		// String with text to render
		vec2D m_characterSize;				// Size of individual char in pixels
		vec2D m_originPoint;				// Top left point where text starts

		int m_scaleOfText = 1;				// Scale of text to display

		SDL_Texture* m_textSprite;			// Pointer to selected text texture

	public:
		// Constructors 
		cText(vec2D p_originPoint);						// Constructor for console text
		cText(vec2D p_originPoint, eTEXT_COLOR p_color);			// Constructor for color text
		cText(vec2D p_originPoint, eTEXT_COLOR p_color, int p_scale);		// Constructor for scaled color text

		// Methods
		int getPixelWidth();				// Returns lenght of rendered text in pixels
		int getPixelHeight();				// Returns height of rendered text in pixels

		void changeTextColor(eTEXT_COLOR p_color);		// Changes color of text
		void setOriginPoint(vec2D p_originPoint);		// Set new origin point of text render

		auto operator()() -> std::string&;			// Access internal string

		void update(const std::string p_newText);		// Changes text which will be displaied
		void draw();
};
