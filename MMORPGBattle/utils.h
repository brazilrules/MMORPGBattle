#pragma once
#include <SDL.h>
#include "Vec3.h"
#include <string>

SDL_Point distanceBetweenPoints(SDL_Point a, SDL_Point b);
Vec3 distanceBetweenVecs(Vec3 a, Vec3 b);

std::string makeHUDString(std::string label, std::string value);