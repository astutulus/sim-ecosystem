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

#include "ConsoleGraphics.h"	// CreateScreenBuffer(), PaintScreenBuffer()
#include "LifeForms.h"		// addGrass(), addRabbit()

/*
Settings
*/
float fGrassSeedRate = 0.02f; // seconds


int main()
{
	/*
	* Global - Time
	*/
	auto tpLastLoopStart = std::chrono::system_clock::now();
	auto tpLastKeyPress = std::chrono::system_clock::now();

	/*
	* Initialise world
	*/
	CreateScreenBuffer();

	addGrass(30, 10);
	addGrass(90, 12);
	addRabbit(5, 5);

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

			std::chrono::duration<float> timeSinceLast = tpNewKeyPress - tpLastKeyPress;
			float fElapsedTime = timeSinceLast.count(); // timeSinceLast has "seconds" after it!
			if (fElapsedTime > fGrassSeedRate)
			{
				int randomX = rand() % getScreenWidth(); // e.g.  rand() % 100;   uses the range 0 to 99 
				int randomY = (rand() % (getScreenHeight() - 2)) + 2;   // to avoid using the top rows

				addGrass(randomX, randomY);
				tpLastKeyPress = std::chrono::system_clock::now();
			}
		}


		/*
		* DRAW
		*/

		PaintScreenBuffer();

	}

	std::cin.get();
}