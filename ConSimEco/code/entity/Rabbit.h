#pragma once

#include "Point.h"
#include "Animal.h"

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

