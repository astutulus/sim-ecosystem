#pragma once

#include <vector>

#include "Point.h"
#include "Entity.h"
#include "LifeForm.h"
#include "Plant.h"

class Animal : public LifeForm
{
protected:
	float fMaxSpeed;
	float eyeSight;
	float fCurrEnergy;
	float fCurrAngle;
	float fCurrSpeed;
public:
	Animal();
	Animal(char, Point, float, int, int);				// name, position, fMaxSpeed, eyeSight, nutrtional value
	float getCurrEnergy();
	Plant* LookForNearestPlant(char, std::vector<Plant*>, float);
	bool FleeFrom(Entity*, float);								// threat, frametime
	bool MoveTowards(Entity*, float);							// target, frametime
	bool Graze(std::vector<Plant*>plants, float);				// choices, frametime
};
