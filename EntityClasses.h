#pragma once

#include <vector>				// vector of candidates, in animal behaviour

/*
* Configuration settings
*/
const float f_GRASS_SEED_RATE = 0.02f; // seconds

const float f_ENERGY_INIT_GRASS = 1.0f;
const float f_ENERGY_INIT_RABBIT = 4.0f;

const float f_ENERGY_TRANSFER_LOOKING = 0.1f;
const float f_ENERGY_TRANSFER_WALKING = 0.5f;
const float f_ENERGY_TRANSFER_EATING = 2.5f;

const int n_RABBIT_MAX_SPEED = 8;

struct Point
{
	float x, y;
	Point(float, float);
	Point();
};

class Entity
{
public:
	char name;
	Point pos;		
	Entity();
	Entity(char, int, int);				//  name, position
	float DistTo(Entity*);
	float AngleTo(Entity*);
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
	Plant(char, int, int, float);			// name, x, y, nutrtional value
};

class Animal : public LifeForm
{
public:
	float fMaxSpeed;
	float eyeSight;
	float fCurrEnergy;
	float fCurrAngle;
	float fCurrSpeed;

	Animal(char, int, int, float, int, int);				// name, x, y, fMaxSpeed, eyeSight, nutrtional value

	Plant* LookForNearestPlant(char, std::vector<Plant*>, float);

	bool FleeFrom(Entity*, float);								// threat, frametime
	bool MoveTowards(Entity*, float);							// target, frametime
	bool Graze(std::vector<Plant*>plants, float);				// choices, frametime
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

