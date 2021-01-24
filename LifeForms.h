#pragma once


/*
* Class Definitions
* 
* Many members are stored internally as float, for necessary accuracy
* but the constr takes integer for api user-friendliness
*/

class Entity
{
public:
	Entity();
	Entity(char, int, int);				//  name, x, y
	char name;
	float xPos, yPos;		
};

class LifeForm : public Entity
{
public:
	LifeForm(char, int, int);			// name, x, y
	float age;
};

class Plant : public LifeForm
{
public:
	Plant(char, int, int, int);			// name, x, y, nutrtional value
	float fNutritionalValue;
};

class Animal : public LifeForm
{
public:
	Animal(char, int, int, int, int);	// name, x, y, MAX_SPEED, eyesight
	float eyeSight;
	float fMaxSpeed;
	float fCurrSpeed;

	bool LookFor(char);
	bool MoveTowards(int, int);
};

class Grass : public Plant
{
public:
	Grass(int, int);					// x, y
};

class Rabbit : public Animal
{
public:
	Rabbit(int, int);					// x, y
};

/*
* Accessors
*/
void addGrass(int, int);
void addRabbit(int, int);
std::vector<Entity*> getEntities();