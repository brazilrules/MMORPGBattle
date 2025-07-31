#pragma once
#include "HUDElement.h"

#define DISPLAY_TIME 30
#define SPEED 3

class PopUpHUDElement:public HUDElement
{
public:
	PopUpHUDElement(TTF_Font* font, std::string label, std::string value, SDL_Rect position, SDL_Color textColor);
	~PopUpHUDElement();
	
	void show();

	void update(int frame, std::string value, SDL_Surface* screen);

private:
	char timer;
};