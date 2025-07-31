#include "Model.h"

Model::Model(int x, int y, int z) : position(x, y , z)
{
}

Model::~Model()
{
}

Vec3 Model::getPosition()
{
	return position;
}

Vec3 Model::getOrigin()
{
	return origin;
}

SDL_Point Model::getScreenSpacePos() {
	return SDL_Point{ position.x, position.y };
}

int Model::getX()
{
	return position.x;
}

void Model::setX(int x)
{
	position.x = x;
}

int Model::getY()
{
	return position.y;
}

void Model::setY(int y)
{
	position.y = y;
}

int Model::getZ()
{
	return position.z;
}

void Model::setZ(int z)
{
	position.z = z;
}

void Model::move(DIRECTION dir)
{
	switch (dir) {
		case BACKWARDS :
			position.z += 1; //speed
			break;
		case LEFT:
			position.x -= 1; //speed
			break;
		case RIGHT:
			position.x += 1; //speed
			break;
		case FORWARDS:
			position.z -= 1; //speed
			break;
	}
}

void Model::stop()
{
	movementVec = Vec3{ 0, 0, 0 };
}

void Model::stop(DIRECTION direction) {
	if (direction == LEFT || direction == RIGHT) movementVec.x = 0;
	if (direction == FORWARDS || direction == BACKWARDS) movementVec.y = 0;

	//if (!movementVec.x && !movementVec.y) moving = STOPPED;
}

void Model::update(int frame, SDL_GLContext context)
{
	//api->drawModel(this);
}