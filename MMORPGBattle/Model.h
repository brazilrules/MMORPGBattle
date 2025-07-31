#pragma once

#include <SDL_render.h>
//#include <SDL_>
#include "Vec3.h"
#include <string>
#include <vector>
#include "GraphicsAPI.h"

enum DIRECTION {
	BACKWARDS,
	LEFT,
	RIGHT,
	FORWARDS
};

enum MOVEMENT {
	STOPPED,
	WALKING,
	RUNNING
};

class Model
{
public:
	Model(int, int, int);
	~Model();

	Vec3 getPosition();
	Vec3 getOrigin();
	
	SDL_Point getScreenSpacePos();

	int getX();
	void setX(int x);
	int getY();
	void setY(int y);
	int getZ();
	void setZ(int z);

	void move(DIRECTION dir);

	void stop();
	void stop(DIRECTION dir);

	void update(int frame, SDL_GLContext context);

private:
	Vec3 position;
	Vec3 origin;

	Vec3 movementVec;

	std::vector<float> vertices;
	std::string vertexShader;
	std::string fragmentShader;

	GraphicsAPI* api;
};