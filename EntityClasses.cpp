#include <vector>

#include "EntityClasses.h"

/*
* Class Definitions
*
* Many members are stored internally as float, for necessary accuracy
* but the constr takes integer for api user-friendliness
*/
Point::Point(float x, float y)
{
		this->x = x;
		this->y = y;
}

Point::Point() : Point(0, 0)
{ }

// Default constr e.g. for use as placeholder in containers
Entity::Entity()
{
	this->name = '-';
	this->pos = Point(0, 0);
}

// Main constr the subclasses use
Entity::Entity(char name, int x, int y)
{
	this->name = name;
	this->pos = Point((float)x, (float)y);
}

float Entity::DistTo(Entity* other)
{
	float dx = (*other).pos.x - this->pos.x;
	float dy = (*other).pos.y - this->pos.y;
	return sqrtf(powf(dx, 2.0f) + powf(dy, 2.0f));
}

float Entity::AngleTo(Entity* other)
{
	float dx = (*other).pos.x - this->pos.x;
	float dy = (*other).pos.y - this->pos.y;
	return atanf(dy / dx);
}

/*
THE FUN PART
*/

LifeForm::LifeForm(char name, int x, int y)
	: Entity(name, x, y)
{
	this->age = 0.0f;
}

Plant::Plant(char name, int x, int y, int nutrition) 
	: LifeForm(name, x, y)
{
	this->fNutritionalValue = (float)nutrition;
}

Animal::Animal(char name, int x, int y, int sight, int maxSp) 
	: LifeForm(name, x, y)
{
	this->fCurrEnergy = 10;
	this->fCurrAngle = 0;
	this->eyeSight = (float)sight;
	this->fMaxSpeed = (float)maxSp;
	this->fCurrSpeed = fMaxSpeed; // to sort
}

Grass::Grass(int x, int y)
	: Plant('G', x, y, n_GRASS_NUTRITION)
{
}

Rabbit::Rabbit(int x, int y)
	: Animal('R', x, y, 30, n_RABBIT_MAX_SPEED)
{
}

/*
* Additional animal object behaviour
*/

Plant* Animal::LookForNearestPlant(char target, std::vector<Plant*> ents){
	bool success = false;			// unused

	Plant* spotted = new Plant('p',10,10,1);
	float fDistToTarget = FLT_MAX;
	for (Plant* ent : ents)
	{
		if (ent->name == target)
		{
			success = true;			// unused
			float dist = this->DistTo(ent);
			if (dist < fDistToTarget)
			{
				spotted = ent;
				fDistToTarget = dist;
			}
		}
	}
	return spotted;
}

bool Animal::FleeFrom(Entity* ent, float looptime)
{
	return false;
}

bool Animal::MoveTowards(Entity* ent, float looptime)
{
	this->fCurrAngle = this->AngleTo(ent);

	this->pos.x += cosf(fCurrAngle) * this->fCurrSpeed * looptime;
	this->pos.y += sinf(fCurrAngle) * this->fCurrSpeed * looptime;

	this->fCurrEnergy -= 0.1f * looptime;
	return true;
}

// Returns true if couldn't see anything to graze
bool Animal::Graze(std::vector<Plant*>plants, float looptime)
{
	Plant* nearestGrass = this->LookForNearestPlant('G', plants);

	if (DistTo(nearestGrass) > 1.0f)
	{
		this->MoveTowards(nearestGrass, looptime);
		return true;
	}
	else if (nearestGrass->fNutritionalValue > 0)
	{
		float fEnergyTransfered = f_ENERGY_TRANSFER_RATE * looptime;
		nearestGrass->fNutritionalValue -= fEnergyTransfered;
		this->fCurrEnergy += fEnergyTransfered;
		return true;
	}
	else
	{
		return false;
	}
}

