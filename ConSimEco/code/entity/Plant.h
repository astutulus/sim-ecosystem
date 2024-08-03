#pragma once

#include "Point.h"
#include "LifeForm.h"

class Plant : public LifeForm
{
protected:
	float fBioMass;
public:
	Plant();
	Plant(char, Point, float);			// name, x, y, nutrtional value
	float getBioMass();
	bool BeConsumed(float);
};
