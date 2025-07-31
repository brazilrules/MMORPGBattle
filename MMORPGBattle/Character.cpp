#include "utils.h";
#include "Character.h"

Character::Character(int hp, int mp, int attack, int defense, int attackRange, std::string spriteFileName, TTF_Font* popUpFont, int x, int y, int z, int speed, int xp)
	:hp(hp), mp(mp), baseAttack(attack), baseDefense(defense), attackRange(attackRange), attacking(false), currentHp(hp),
	currentMp(mp), model(Model(x, y, z)), xp(xp)
{
	SDL_Rect popUpPos{ model.getOrigin().x, model.getOrigin().y};
	damagePopUp = new PopUpHUDElement(popUpFont, "", "", popUpPos, SDL_Color {255, 0, 0, 255});
}

Character::~Character()
{
}

int Character::getHP() { return currentHp; }

int Character::getMP() { return currentMp; }

int Character::getAttack() { return baseAttack; }

int Character::getDefense() { return baseDefense; }

//int Character::getAttackRange() { return attackRange; }

bool Character::isAttacking() { return attacking; }

Model& Character::getModel() {
	return model;
}

int Character::getXP() { return xp; }

void Character::attackEnemy(Character& target) {
	if (currentHp && target.getHP()) {
		if (!attacking) attacking = true;

		Vec3 distance = distanceBetweenVecs(model.getOrigin(), target.getModel().getOrigin());

		if (distance.x > (attackRange /*+ model.getFrameWidth() / 2 */) || distance.y > (attackRange /*+ sprite.getFrameHeight() / 2 */ )) {
			//sprite.moveTowards(target.getSprite().getCenter());
		}
		else {
			//sprite.stop();
			if (!attackTime) {
				target.takeDamage(std::max(getAttack() - target.getDefense(), 0));
				SDL_Point targetPos{ target.getModel().getOrigin().x, target.getModel().getOrigin().y };
				target.damagePopUp->setPosition(targetPos);
				((PopUpHUDElement*)target.damagePopUp)->show();
				attackTime = 100;
				attacking = false;
			}
		}
	}
}

void Character::takeDamage(int damage) {
	damagePopUp->setValue(std::to_string(damage));
	currentHp = std::min(std::max(currentHp - damage, 0), hp);
}

void Character::update(int frame, SDL_Surface* screen) {
	if (attackTime) attackTime--;
	if (currentHp) {
		model.update(frame, screen);
	}
	damagePopUp->update(frame, "", screen);
}