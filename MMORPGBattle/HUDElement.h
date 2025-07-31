#pragma once

#include <SDL_surface.h>
#include <string>
#include <SDL_ttf.h>

class HUDElement
{
public:
	HUDElement(TTF_Font* font, std::string label, std::string value, SDL_Rect position, SDL_Color textColor = {255, 255, 255, 255});
	~HUDElement();

	void setValue(std::string val);
	void setPosition(SDL_Point pos);

	virtual void update(int frame, std::string value, SDL_Surface* screen);

protected:
SDL_Rect position;

private:
	TTF_Font* font;
	std::string label;
	std::string value;

	SDL_Color textColor;
	SDL_Surface* surface;
};
