#include "HUDElement.h"
#include "utils.h"

HUDElement::HUDElement(TTF_Font* font, std::string label, std::string value, SDL_Rect position, SDL_Color textColor)
	:font(font), label(label), value(value), position(position), textColor(textColor)
{
	std::string text = makeHUDString(label, value);
	surface = TTF_RenderText_Solid(font, text.c_str(), textColor);
}

HUDElement::~HUDElement()
{
	SDL_FreeSurface(surface);
}

void HUDElement::setValue(std::string val) {
	value = val;
	SDL_FreeSurface(surface);
	std::string text = makeHUDString(label, value);
	surface = TTF_RenderText_Solid(font, text.c_str(), textColor);
}

void HUDElement::setPosition(SDL_Point pos) {
	position.x = pos.x;
	position.y = pos.y;
}

void HUDElement::update(int frame, std::string value, SDL_Surface* screen) {
	if (!value.empty()) setValue(value);
	//TODO: Render surface with OpenGL
}