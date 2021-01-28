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

Plant::Plant(char name, int x, int y, float nutrition) 
	: LifeForm(name, x, y)
{
	this->fNutritionalValue = nutrition;
}

Animal::Animal(char name, int x, int y, float nutrition, int sight, int maxSp)
	: LifeForm(name, x, y)
{
	this->fCurrEnergy = nutrition;
	this->fCurrAngle = 0;
	this->eyeSight = (float)sight;
	this->fMaxSpeed = (float)maxSp;
	this->fCurrSpeed = fMaxSpeed; // to sort
}

Grass::Grass(int x, int y)
	: Plant('G', x, y, f_ENERGY_INIT_GRASS)
{
}

Rabbit::Rabbit(int x, int y)
	: Animal('R', x, y, f_ENERGY_INIT_RABBIT, 30, n_RABBIT_MAX_SPEED)
{
}

/*
* Additional animal object behaviour
*/

/*
Returns the nearest plant or NULL
*/
Plant* Animal::LookForNearestPlant(char target, std::vector<Plant*> ents, float looptime)
{
	Plant* result = NULL;
	if (ents.size() > 0)
	{
		float fDistToTarget = FLT_MAX;
		for (Plant* ent : ents)
		{
			if (ent->name == target)
			{
				float dist = this->DistTo(ent);
				if (dist < fDistToTarget)
				{
					result = ent;
					fDistToTarget = dist;
				}
			}
		}
	}
	this->fCurrEnergy -= f_ENERGY_TRANSFER_LOOKING * looptime;
	return result;
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

	this->fCurrEnergy -= f_ENERGY_TRANSFER_WALKING * looptime;

	return true;
}

// Returns true if couldn't see anything to graze
bool Animal::Graze(std::vector<Plant*> plants, float looptime)
{
	Plant* nearestGrass = this->LookForNearestPlant('G', plants, looptime);
	if (nearestGrass)
	{
		if (DistTo(nearestGrass) > 1.0f)
		{
			this->MoveTowards(nearestGrass, looptime);
			return true;
		}
		else if (nearestGrass->fNutritionalValue > 0)
		{
			float fEnergyTransfered = f_ENERGY_TRANSFER_EATING * looptime;

			nearestGrass->fNutritionalValue -= fEnergyTransfered;
			this->fCurrEnergy += fEnergyTransfered;
			return true;
		}
	}
	return false;
}
