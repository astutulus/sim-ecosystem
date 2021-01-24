#pragma once


/*
* Class Definitions
*/

class Entity
{
public:
	char name;
	float xPos, yPos;		// stored internally as float for necessary accuracy,
	Entity(char, int, int);	// even though constr takes int for user friendliness
};


class Grass : public Entity
{
public:
	Grass(int, int);
};


class Rabbit : public Entity
{
public:
	int speed = 0;
	int MAX_SPEED = 20;
	int eyesight = 20;
	Rabbit(int, int, int);
	void Move(int, int);
	bool MoveToBNearestGrass();
};

/*
* Accessors
*/
void addGrass(int, int);
void addRabbit(int, int, int);
std::vector<Entity*> getEntities();