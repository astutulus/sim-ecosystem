#pragma once

#include "point.h"
#include "animal.h"

class Rabbit : public Animal
{
public:
	Rabbit();
	Rabbit(Point);
};


class Fox : public Animal
{
public:
	Fox();
	Fox(Point);
};

