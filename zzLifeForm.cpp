
#include "GameEngine.h"
#include "Point.h"
#include "zzLifeForm.h"


LifeForm::LifeForm() : Entity(), age{ 0.0f }
{ }

LifeForm::LifeForm(char name, Point position)
	: Entity(name, position), age{ 0.0f }
{ }

