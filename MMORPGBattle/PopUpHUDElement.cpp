#include "PopUpHUDElement.h"

PopUpHUDElement::PopUpHUDElement(TTF_Font* font, std::string label, std::string value, SDL_Rect position, SDL_Color textColor)
	: HUDElement(font, label, value, position, textColor), timer(0)
{
}

PopUpHUDElement::~PopUpHUDElement()
{
}

void PopUpHUDElement::show() {
	timer = DISPLAY_TIME;
}

void PopUpHUDElement::update(int frame, std::string value, SDL_Surface* screen) {
	if (timer) {
		position.y -= SPEED;
		HUDElement::update(frame, value, screen);
		timer--;
	}
}