#include "Player.h"
#include <iostream>

Player::Player(int hp, int mp, int attack, int defense, int attackRange, int strength, int vitality, int intelligence, std::string spriteFileName, TTF_Font* popUpFont, std::vector<Skill> skills)
	:Character(hp, mp, attack, defense, attackRange, spriteFileName, popUpFont), strength(strength), vitality(vitality), intelligence(intelligence), skills(skills)
{
}

Player::~Player()
{
}

int Player::getAttack() {
	return baseAttack + strength;
}

int Player::getDefense() {
	return baseDefense + vitality;
}

void Player::calculateAttributes() {
	hp = hp + (vitality * 10);
	mp = mp + (intelligence * 5);
}

void Player::levelUp(int strPlus, int vitPlus, int intPlus) {
	strength = strPlus;
	vitality = vitPlus;
	intelligence = intPlus;
	int hpPercent = currentHp / hp;
	int mpPercent = currentMp / mp;
	calculateAttributes();
	currentHp = hp * hpPercent;
	currentMp = mp * mpPercent;
}