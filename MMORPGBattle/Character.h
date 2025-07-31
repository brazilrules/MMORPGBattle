#pragma once
#include "Model.h"
#include "PopUpHUDElement.h"

class Character
{
public:
	Character(int, int, int, int, int, std::string, TTF_Font*, int = 0, int = 0, int = 0, int = 5, int = 0);
	~Character();

	int getHP();
	int getMP();

	virtual int getAttack();
	virtual int getDefense();
	//int getAttackRange();

	bool isAttacking();

	Model& getModel();

	int getXP();

	void attackEnemy(Character& target);
	void takeDamage(int damage);
	//void die();

	void update(int frame, SDL_Surface* screen);

protected:
	int hp;
	int currentHp;
	int mp;
	int currentMp;

	int baseAttack;
	int baseDefense;

	int xp;

private:
	int attackRange;

	bool attacking;
	short attackTime = 0;

	Model model;
	HUDElement* damagePopUp;
};

