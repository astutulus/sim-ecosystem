#include <vector>

#include "EntityClasses.h"			// For class definitions
#include "Simulation.h"	// Points and distances
#include "ConSimEco.h"			// Constants

/*
* Class implementation
*/

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
	this->pos = Point(x, y);
}

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
	this->energy = 10;
	this->angle = 0;
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
			float dist = DistToPoint(this->pos, ent->pos);
			if (dist < fDistToTarget)
			{
				spotted = ent;
				fDistToTarget = dist;
			}
		}
	}
	return spotted;
}


bool Animal::MoveTowards(Entity* ent, float frameTime)
{	
	this->angle = AngleToPoint(this->pos, ent->pos);

	this->pos.x += cosf(angle) * this->fCurrSpeed * frameTime;
	this->pos.y += sinf(angle) * this->fCurrSpeed * frameTime;

	this->energy -= 0.1f * frameTime;
	return true;
}


bool Animal::FleeFrom(Entity* ent)
{
	return false;
}


bool Animal::Graze(std::vector<Plant*>plants, float fLoopDuration)
{
	Plant* nearestGrass = this->LookForNearestPlant('G', plants);

	if (DistToPoint(this->pos, nearestGrass->pos) > 1.0f)
	{
		this->MoveTowards(nearestGrass, fLoopDuration);
	}
	else 
	{
		this->Consume(nearestGrass, fLoopDuration);
	}
	return true;
}


bool Animal::Consume(Plant* fodder, float fLoopDuration)
{
	if (fodder->fNutritionalValue > 0)
	{
		float fEnergyTransfered = f_ENERGY_TRANSFER_RATE * fLoopDuration;

		fodder->fNutritionalValue -= fEnergyTransfered;
		this->energy += fEnergyTransfered;
	}
	return true;
}

