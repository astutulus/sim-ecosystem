#pragma once

#include "Point.h"


class Entity
{
protected:
	char name;
	Point pos;		
public:
	Entity();
	Entity(char, Point);
	char getName();
	Point getPos();
	float DistTo(Entity*);
	float AngleTo(Entity*);
};
