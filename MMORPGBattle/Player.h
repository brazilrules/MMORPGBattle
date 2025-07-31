#pragma once
#include <vector>
#include "Character.h"
#include "Skill.h"

class Player:public Character
{
public:
	Player(int, int, int, int, int, int, int, int, std::string, TTF_Font*, std::vector<Skill>);
	~Player();

	int getAttack();
	int getDefense();

	void calculateAttributes();
	void levelUp(int, int, int);

private:
	int strength;
	int vitality;
	int intelligence;

	std::vector<Skill> skills;
};