
#include "GameEngine.h"
#include "Point.h"
#include "zzzAnimal.h"
#include "zzzPlant.h"


Animal::Animal() : LifeForm()
{
}

Animal::Animal(char name, Point position, float nutrition, int sight, int maxSp)
	: LifeForm(name, position)
{
	this->fCurrEnergy = nutrition;
	this->fCurrAngle = 0;
	this->eyeSight = (float)sight;
	this->fMaxSpeed = (float)maxSp;
	this->fCurrSpeed = fMaxSpeed; // to sort
}

float Animal::getCurrEnergy()
{
	return this->fCurrEnergy;
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
			if (ent->getName() == target)
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
		else if (nearestGrass->getBioMass() > 0)
		{
			float fEnergyTransfered = f_ENERGY_TRANSFER_EATING * looptime;

			nearestGrass->BeConsumed(fEnergyTransfered);
			this->fCurrEnergy += fEnergyTransfered;
			return true;
		}
	}
	return false;
}
