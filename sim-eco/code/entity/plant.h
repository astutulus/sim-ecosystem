#pragma once

#include "point.h"
#include "life-form.h"

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
