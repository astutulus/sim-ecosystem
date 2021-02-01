#pragma once

#include "Point.h"
#include "zEntity.h"


class LifeForm : public Entity
{
protected:
	float age;
public:
	LifeForm();
	LifeForm(char, Point);
};
