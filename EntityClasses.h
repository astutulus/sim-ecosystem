#pragma once

#include <vector>

#include "Simulation.h"

/*
* Class Definitions
* 
* Many members are stored internally as float, for necessary accuracy
* but the constr takes integer for api user-friendliness
*/

class Entity
{
public:
	char name;
	Point pos;		
	Entity();
	Entity(char, int, int);				//  name, position
};

class LifeForm : public Entity
{
public:
	float age;
	LifeForm(char, int, int);			// name, x, y
};

class Plant : public LifeForm
{
public:
	float fNutritionalValue;
	Plant(char, int, int, int);			// name, x, y, nutrtional value
};

class Animal : public LifeForm
{
public:
	float angle;
	float eyeSight;
	float fMaxSpeed;
	float fCurrSpeed;
	float energy;
	Animal(char, int, int, int, int);				// name, x, y, MAX_SPEED, eyesight
	bool FleeFrom(Entity*);										// threat, frametime
	Plant* LookForNearestPlant(char, std::vector<Plant*>);
	bool Graze(std::vector<Plant*>plants, float fLoopDuration);
	bool MoveTowards(Entity*, float);							// target, frametime
	bool Consume(Plant*, float);								// target, frametime
};

class Grass : public Plant
{
public:
	Grass(int, int);					// x, y
};

class Rabbit : public Animal
{
public:
	Rabbit(int, int);					// x, y
};

