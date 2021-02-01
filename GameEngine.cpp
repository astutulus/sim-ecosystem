#include "DisplayEngine.h"
#include "GameEngine.h"
#include "Point.h"
#include "zEntity.h"
#include "zzzzGrass.h"
#include "zzzzRabbit.h"

EcoSim::EcoSim()
{
	tpLastKeyPress = std::chrono::system_clock::now();
	tpLastLoopStart = std::chrono::system_clock::now();
	tpThisLoopStart = std::chrono::system_clock::now();

	looptime = 0.001;

	display = new DisplayObj();
}

void EcoSim::SpawnGrass()
{
	int randX = rand() % display->getScreenWidth(); // e.g.  rand() % 100;   uses the range 0 to 99 
	int randY = (rand() % (display->getScreenHeight() - 2)) + 2;   // to avoid using the top rows
	SpawnGrass(randX, randY);
}

void EcoSim::SpawnGrass(int x, int y)
{	
	this->plants.push_back(new Grass(Point(x, y)));
}

void EcoSim::SpawnRabbit()
{
	int randX = rand() % display->getScreenWidth(); // e.g.  rand() % 100;   uses the range 0 to 99 
	int randY = (rand() % (display->getScreenHeight() - 2)) + 2;   // to avoid using the top rows
	SpawnRabbit(randX, randY);
}

void EcoSim::SpawnRabbit(int x, int y)
{
	animals.push_back(new Rabbit(Point(x, y)));	
}

bool EcoSim::IsKeyPressed(char key)
{
	if (GetAsyncKeyState((unsigned short)key) & 0x8000)
	{
		auto tpNewKeyPress = std::chrono::system_clock::now();
		std::chrono::duration<float> timeSinceLastPress = tpNewKeyPress - tpLastKeyPress;

		// timeSinceLastPress has "seconds" after it, so get count()!

		if (timeSinceLastPress.count() > f_GRASS_SEED_RATE)
		{
			tpLastKeyPress = tpNewKeyPress;
			return true;
		}
	}
	return false;
}

void EcoSim::UpdateLoopTime()
{
	this->looptime = this->GetLoopTime();
}

bool EcoSim::AninalAcivity()
{
	{
		// in future make threaded
		for (Animal* anml : animals)
		{
			anml->Graze(plants, looptime);
			if (anml->getCurrEnergy() <= 0)
			{
				animals.erase(std::remove(animals.begin(), animals.end(), anml));
			}
		}

		if (this->animals.size() == 0) 
			return false;
		else 
			return true;
	}
}

bool EcoSim::PlantAcivity()
{
	for (Plant* plnt : plants)
	{
		if (plnt->getBioMass() <= 0)
		{
			plants.erase(std::remove(plants.begin(), plants.end(), plnt));
		}
	}

	if (this->plants.size() == 0)
		return false;
	else
		return true;

}

void EcoSim::DrawAll()
{
	display->BufferWipe();  // phase out when actors are able to wipe their own footprints

	for (Plant* plnt : plants)
	{
		BufferActor(plnt);
	}
	for (Animal* anml : animals)
	{
		BufferActor(anml);
	}

	// Show energy level of the first-born Rabbit still alive
	display->BufferAddStats((*(animals.begin()))->getCurrEnergy());

	display->PaintBuffer();
}


float EcoSim::GetLoopTime()
{
	tpThisLoopStart = std::chrono::system_clock::now();
	std::chrono::duration<float> loopDuration = tpThisLoopStart - tpLastLoopStart;
	tpLastLoopStart = tpThisLoopStart;
	return loopDuration.count();
}

void EcoSim::BufferActor(Entity* ent)
{
	Entity e = *ent;
	Point p = e.getPos();
	display->BufferAddCharacter(e.getName(), e.getPos().x, e.getPos().y);
}
