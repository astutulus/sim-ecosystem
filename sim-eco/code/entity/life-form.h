#pragma once

#include "point.h"
#include "entity.h"


class LifeForm : public Entity
{
protected:
	float age;
public:
	LifeForm();
	LifeForm(char, Point);
};
