#include <vector>

#include "LifeForms.h"		// For class definitions

/*
* Database - The definitive heart & soul of the game
*/
static std::vector<Entity*> entities;


/*
* Class implementation
*/

// Default constr e.g. for use as placeholder in containers
Entity::Entity()
{
	this->name = '-';
	this->xPos = 0.0f;
	this->yPos = 0.0f;
}

// Main constr the subclasses use
Entity::Entity(char name, int x, int y)
{
	this->name = name;
	this->xPos = (float)x;
	this->yPos = (float)y;
}

LifeForm::LifeForm(char name, int x, int y)
	: Entity(name, x, y)
{
	this->age = 0.0f;
};

Plant::Plant(char name, int x, int y, int nutrition) 
	: LifeForm(name, x, y)
{
	this->fNutritionalValue = (float)nutrition;
};

Animal::Animal(char name, int x, int y, int sight, int maxSp) 
	: LifeForm(name, x, y)
{
	this->eyeSight = (float)sight;
	this->fMaxSpeed = (float)maxSp;
	this->fCurrSpeed = 0.0f;
};

Grass::Grass(int x, int y)
	: Plant('G', x, y, 10)
{
};

Rabbit::Rabbit(int x, int y)
	: Animal('R', x, y, 20, 50)
{
};

/*
* Returns false if no grass seen and so, no action taken
*/
bool Animal::LookFor(char target){
	bool success = false;

	Entity* nearestGrass;
	float nearestGrassDist = FLT_MAX;
	for (Entity* ent : getEntities())
	{
		if (ent->name == target)
		{
			success = true;
			float dx = ent->xPos - this->xPos;
			float dy = ent->yPos - this->yPos;
			float dist = sqrtf(powf(dx, 2.0f) + powf(dy, 2.0f));
			if (dist < nearestGrassDist)
			{
				nearestGrass = ent;
				nearestGrassDist = dist;
			}
		}
	}

	return success;
}


/*
* Additional animal object behaviour
*/
bool Animal::MoveTowards(int deltaX, int deltaY)
{
	xPos += (deltaX * this->fMaxSpeed);
	yPos += (deltaY * this->fMaxSpeed);
	return true;
}


/*
* Accessors - To populate the world and retrieve it
*/
void addGrass(int xSpawn, int ySpawn)
{
	Grass* cedric = new Grass(xSpawn, ySpawn);
	entities.push_back(cedric);
}

void addRabbit(int xSpawn, int ySpawn)
{
	Rabbit* peter = new Rabbit(xSpawn, ySpawn);
	entities.push_back(peter);
}

std::vector<Entity*> getEntities()
{
	return entities;
}

