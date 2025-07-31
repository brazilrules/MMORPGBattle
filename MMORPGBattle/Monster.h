#pragma once
#include "Character.h"

class Monster:public Character
{
public:
	Monster(int, int, int, int, int, std::string, TTF_Font*, int, int, int, int, int, int = 3);
	~Monster();

	void checkPlayerProximity(Character& player);

private:
	int aggroRange;
};