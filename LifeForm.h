#pragma once

#include "Point.h"
#include "Entity.h"


class LifeForm : public Entity
{
protected:
	float age;
public:
	LifeForm();
	LifeForm(char, Point);
};
