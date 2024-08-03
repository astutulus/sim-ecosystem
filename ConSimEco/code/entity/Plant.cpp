
#include "GameEngine.h"
#include "Point.h"
#include "Plant.h"

Plant::Plant() : LifeForm(), fBioMass{ 1 }
{}

Plant::Plant(char name, Point position, float nutrition)
	: LifeForm(name, position), fBioMass{ nutrition }
{}

float Plant::getBioMass()
{
	return fBioMass;
}

/*
* Return false if plant is hereby completely consumed
*/
bool Plant::BeConsumed(float eaten)
{
	bool success = true;
	this->fBioMass -= eaten;
	if (this->fBioMass < 0)
	{
		this->fBioMass = 0;
		success = false;
	}
	return success;
}
