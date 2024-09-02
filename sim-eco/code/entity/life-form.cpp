#include "game-engine.h"
#include "point.h"
#include "life-form.h"


LifeForm::LifeForm() : Entity(), age{ 0.0f }
{ }

LifeForm::LifeForm(char name, Point position)
	: Entity(name, position), age{ 0.0f }
{ }

