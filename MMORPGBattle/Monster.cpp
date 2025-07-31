#include "utils.h"
#include "Monster.h"

Monster::Monster(int hp, int mp, int attack, int defense, int attackRange, std::string spriteFileName, TTF_Font* popUpFont, int xp, int aggroRange, int x, int y, int z, int speed)
	:Character(hp, mp, attack, defense, attackRange, spriteFileName, popUpFont, x, y, z, speed, xp), aggroRange(aggroRange)
{
}

Monster::~Monster()
{
}

void Monster::checkPlayerProximity(Character& player) {
	if (currentHp) {
		Vec3 distance = distanceBetweenVecs(getModel().getPosition(), player.getModel().getPosition());

		if (distance.x < aggroRange && distance.y < aggroRange && distance.z < aggroRange) attackEnemy(player);
		else getModel().stop();
	}
}