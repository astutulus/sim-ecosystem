#include <vector>

#include "LifeForms.h"		// For class definitions

/*
* Database - The definitive heart & soul of the game
*/
static std::vector<Entity*> entities;


/* 
* Class implementation
* I notice I have no default constructors, just our overloaded ones
*/
Entity::Entity(char name, int xInit, int yInit)
{
	this->name = name;
	xPos = (float)xInit;
	yPos = (float)yInit;
}

Grass::Grass(int xInit, int yInit) : Entity('G', xInit, yInit)
{

}

Rabbit::Rabbit(int xInit, int yInit, int speed) : Entity('R', xInit, yInit)
{
	if ((speed >= 0) && (speed < MAX_SPEED))
	{
		this->speed = speed;
	}
}

/*
* Additional animal object behaviour
*/
void Rabbit::Move(int deltaX, int deltaY)
{
	xPos += (deltaX * speed);
	yPos += (deltaY * speed);
}

/*
* Returns false if no grass seen and so, no action taken
*/
bool Rabbit::MoveToBNearestGrass(){
	bool success = false;

	Entity* nearestGrass;
	float nearestGrassDist = FLT_MAX;
	for (Entity* ent : getEntities())
	{
		if (ent->name == 'G')
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
* Accessors - To populate the world and retrieve it
*/
void addGrass(int xSpawn, int ySpawn)
{
	Grass* cedric = new Grass(xSpawn, ySpawn);
	entities.push_back(cedric);
}

void addRabbit(int xSpawn, int ySpawn, int speed)
{
	Rabbit* peter = new Rabbit(xSpawn, ySpawn, speed);
	entities.push_back(peter);
}

std::vector<Entity*> getEntities()
{
	return entities;
}

