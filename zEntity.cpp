#define _USE_MATH_DEFINES // required for the next line to work
#include <cmath>
#include <vector>

#include "GameEngine.h"
#include "Point.h"
#include "zEntity.h"

Entity::Entity() : name { '-' }, pos { Point(0, 0) }
{}


Entity::Entity(char name, Point position) : name{ name }, pos{ position }
{ }

char Entity::getName()
{
	return this->name;
}

Point Entity::getPos()
{
	return this->pos;
}

float Entity::DistTo(Entity* other)
{
	float dx = (*other).pos.x - this->pos.x;
	float dy = (*other).pos.y - this->pos.y;
	return sqrtf(powf(dx, 2.0f) + powf(dy, 2.0f));
}

float Entity::AngleTo(Entity* other)
{
	float dx = (*other).pos.x - this->pos.x;
	float dy = (*other).pos.y - this->pos.y;

	if (dx > 0)
		return atanf(dy / dx);
	else
		return atanf(dy / dx) + M_PI;
}

