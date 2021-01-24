#include <iostream>
#define LOG(x) std::cout << x << std::endl;

/*
* ------------------------------
* Simulated Ecosystem in Console
* ------ by Robin Wootton ------
* ------------------------------
*
* To do:-
* 
*/

#include "Windows.h"	// GetAsyncKeyState()

#include <chrono>		// std::chrono::system_clock::now(), std::chrono::duration<>
#include <random>		// rand()

#include "ConsoleGraphics.h"	// CreateScreenBuffer(), PaintEntities()
#include "EntityClasses.h"			// addGrass(), addRabbit()
#include "ConSimEco.h"			// Constants


int main()
{

	/*
	* Global variables
	*/
	auto tpLastLoopStart = std::chrono::system_clock::now();
	auto tpLastDrawn = std::chrono::system_clock::now();

	std::vector<Plant*> plants;
	Grass* cedric = new Grass(40, 5);
	plants.push_back(cedric);

	Grass* cecil = new Grass(70, 25);
	plants.push_back(cecil);

	Rabbit* peter = new Rabbit(20, 15);

	/*
	* Initialise graphics
	*/
	CreateScreenBuffer();

	/*
	* GAME LOOP
	*/
	bool running = true;
	while (running)
	{
		/*
		* TIMING
		*/
		auto tpThisLoopStart = std::chrono::system_clock::now();
		std::chrono::duration<float> loopDuration = tpThisLoopStart - tpLastLoopStart;
		tpLastLoopStart = tpThisLoopStart;

		float fLoopDuration = loopDuration.count();

		/*
		* CONTROL
		*/

		// Add random grass
		if (GetAsyncKeyState((unsigned short)'G') & 0x8000)
		{
			auto tpNewKeyPress = std::chrono::system_clock::now();
			std::chrono::duration<float> timeSinceLast = tpNewKeyPress - tpLastDrawn;
			float fElapsedTime = timeSinceLast.count(); // timeSinceLast has "seconds" after it!

			if (fElapsedTime > f_GRASS_SEED_RATE)
			{
				int randomX = rand() % getScreenWidth(); // e.g.  rand() % 100;   uses the range 0 to 99 
				int randomY = (rand() % (getScreenHeight() - 2)) + 2;   // to avoid using the top rows

				Grass* cecil = new Grass(randomX, randomY);
				plants.push_back(cecil);

				tpLastDrawn = std::chrono::system_clock::now();
			}
		}

		/*
		RUN SIMULATION
		*/
		peter->Graze(plants, fLoopDuration);

		// Cleanup consumed plants
		for (Plant* p : plants)
		{
			if (p->fNutritionalValue < 0)
			{
				// delete p;

				plants.erase(    std::remove(plants.begin(), plants.end(), p)       );

			
			}
		}




		/*
		* DRAW
		*/

		WipeScreenBuffer(); // phase out when rabbit moves and wipes footprints

		for (Plant* p : plants)
		{
			PaintEntity(p);
		}

		PaintEntity(peter);
		PaintStats(peter);

		PaintToScreen();
	}

	std::cin.get();
}